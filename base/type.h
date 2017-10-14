#ifndef LLAMA_TYPE_H
#define LLAMA_TYPE_H

#include <cstdint>
#include <string>

#include "base/numeric_type.h"

namespace llama {

  // Core identifier of data types in the llama type system.
  //
  // Types are encoded into a 32-bit integer code as follows:
  //
  //   bits 0-7:  category
  //   bits 8-31: category params
  //
  // Each category defines its required params, which must fit into 28 bits and
  // specify the format of the data represented by the type.
  class type {
  public:
    enum category {
      kTypeUndefined  = 0,
      kTypeNumeric    = 1,
      kTypeString     = 2,
      kTypeEnum	      = 3,
      kTypeTuple      = 4,
      kTypeArray      = 5,
      kTypeDictionary = 6,
      kTypeBuffer     = 7,
      kTypeCustom     = 8
    };

    using scalar_type = numeric_type::scalar_type;
    
    // Static contructors for numeric types.
    // =====================================================================
    static type make_numeric_type(scalar_type scalar,
				  std::uint8_t bit_depth,
				  std::initializer_list<std::uint8_t> dims) {
      return type(numeric_type::encode(scalar, bit_depth, dims));
    }

    static type make_int(std::int8_t bit_depth) {
      return make_numeric_type(numeric_type::kScalarInt, bit_depth, {});
    }
    
    static type make_uint(std::int8_t bit_depth) {
      return make_numeric_type(numeric_type::kScalarUInt, bit_depth, {});
    }

    static type make_float(std::int8_t bit_depth) {
      return make_numeric_type(numeric_type::kScalarFloat, bit_depth, {});
    }
    
    static type make_vector(type scalar, std::uint8_t dim);
    
    static type make_matrix(type scalar, std::uint8_t row_dim,
			    std::uint8_t col_dim);

    // Accessors for all types.
    // =====================================================================
    category get_category() const {
      return static_cast<category>(m_code & kMaskCategory);
    }

    bool is_defined() const { return get_category() != kTypeUndefined; }

    std::string get_type_name() const;
    
    // Accessors for numeric types.
    // =====================================================================
    bool is_numeric() const { return get_category() == kTypeNumeric; }

    bool is_scalar() const {
      return is_numeric() && numeric_type::get_rank(m_code) == 0;
    }

    scalar_type get_scalar_type() const {
      assert(is_numeric());
      return numeric_type::get_scalar_type(m_code);
    }

    std::uint8_t get_bit_depth() const {
      assert(is_numeric());
      return numeric_type::get_bit_depth(m_code);
    }
    
  private:
    static constexpr std::uint32_t kMaskCategory = 0xf;

    type(std::uint32_t code) : m_code(code) {}
    
    std::uint32_t m_code;
  };

  template<typename T> type type_of();
  template<typename T> std::string type_name() {
    return type_of<T>().get_type_name();
  }
  
  template<> inline type type_of<std::int8_t>()  { return type::make_int(8);  }
  template<> inline type type_of<std::int16_t>() { return type::make_int(16); }
  template<> inline type type_of<std::int32_t>() { return type::make_int(32); }
  template<> inline type type_of<std::int64_t>() { return type::make_int(64); }

  template<>
  inline type type_of<std::uint8_t>()  { return type::make_uint(8);  }
  template<>
  inline type type_of<std::uint16_t>() { return type::make_uint(16); }
  template<>
  inline type type_of<std::uint32_t>() { return type::make_uint(32); }
  template<>
  inline type type_of<std::uint64_t>() { return type::make_uint(64); }

  template<> inline type type_of<float>()  { return type::make_float(32); }
  template<> inline type type_of<double>() { return type::make_float(64); }
  
} // namespace llama

#endif // LLAMA_TYPE_H
