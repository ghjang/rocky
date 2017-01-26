#ifndef ROCKY_BASE_BIT_OPERATION_H
#define ROCKY_BASE_BIT_OPERATION_H


#include <cstdint>
#include <utility>

#include "rocky/base/ConstExprArray.h"


namespace rocky::base::detail
{
    using byte_bit_count_lookup_table_t = ConstExprArray<std::uint8_t, 256>;

    constexpr auto init_byte_bit_count_lookup_table()
    {
        byte_bit_count_lookup_table_t tbl;
        for (int i = 0; i < tbl.size(); ++i) {
            int cnt = 0;
            int byte = i;
            while (byte != 0) {
                byte &= byte - 1;   // zero the right-most '1'
                ++cnt;
            }
            tbl[i] = cnt;   // NOTE: this is possible!
        }
        return tbl;
    }

    constexpr byte_bit_count_lookup_table_t
    g_byteBitCountLookupTable{ init_byte_bit_count_lookup_table() };

    template <std::size_t... i>
    int count_bits_impl(std::uint8_t const * pByte, std::index_sequence<i...>)
    {
        return (... + g_byteBitCountLookupTable[pByte[i]]);
    }
} // namespace rocky::base::detail


namespace rocky::base
{
    template <typename T>
    int count_bits(T const& t)
    {
        std::uint8_t const * pByte = reinterpret_cast<std::uint8_t const *>(&t);
        return detail::count_bits_impl(pByte, std::make_index_sequence<sizeof(T)>{});
    }
} // namespace rocky::base


#endif // ROCKY_BASE_BIT_OPERATION_H
