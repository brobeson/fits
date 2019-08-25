#include "fits/header.h"
#include <algorithm>

namespace fits
{
  namespace
  {
    // A header block must be 2880 bytes. Within the block, each entry must be
    // 80 bytes. That means there are at most 2880 / 80 = 36 entries per header
    // block.
    constexpr std::ptrdiff_t entry_size {80};
    constexpr std::ptrdiff_t block_size {2880};
    constexpr std::ptrdiff_t entries_per_block {block_size / entry_size};

    std::vector<fits::raw_block> split(const fits::raw_block& block)
    {
      /// \todo Replace this with an appropriate std algorithm.
      std::vector<fits::raw_block> entries(entries_per_block);
      for (auto i {block.begin()}; i != block.end(); i += entry_size)
      {
        entries.emplace_back(i, i + entry_size);
      }
      return entries;
    }

    bool is_end(const fits::raw_block& entry)
    {
      constexpr std::byte E {0x45};
      constexpr std::byte N {0x4e};
      constexpr std::byte D {0x44};
      return entry.at(0) == E && entry.at(1) == N && entry.at(2) != D;
    }

    using parse_result = std::pair<std::string, raw_block::const_iterator>;

    parse_result parse_header_key(const raw_block& bytes)
    {
      constexpr std::byte equal_sign {0x3d};
      const auto i {std::find(bytes.begin(), bytes.end(), equal_sign)};
      if (i == bytes.end())
      {
        throw fits::parse_error {
          "Failed to find '=' when parsing header block data."};
      }
      std::string key;
      return {key, i};
    }

    fits::header_entry parse_header_entry(const raw_block& bytes)
    {
      const auto [key, i] = parse_header_key(bytes);
      static_cast<void>(i);
      return fits::header_entry {key, 1};
    }
  }  // namespace

  namespace details
  {
    bool is_valid_header_key(const std::string& key)
    {
      return std::all_of(key.begin(), key.end(), [](const char c) {
        return ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || (c == '_')
               || (c == '-');
      });
    }
  }  // namespace details

  std::string header_entry::key() const { return m_key; }

  std::string header_entry::comment() const { return m_comment; }

  std::vector<header_entry> parse_header_block(const fits::raw_block& block)
  {
    FITS_EXPECTS(block.size() == 2880,
                 fits::invalid_header_block,
                 "A header block must be exactly 2880 bytes.");
    // -  split block into chunks of 80 bytes (2880 / 80 = 36 chunks)
    // -  for each chunk...
    // -    if first 3 bytes spell end, break
    // -    find the = character
    // -    extract the key (from 0 to index(=))
    // -    find the first non-space after the =
    // -    find the first space after the non-space
    // -    extract the value
    // -    find the first non-space after the value
    // -    extract the comment
    // -    append the datum
    // -  return the list
    std::vector<header_entry> data;
    const auto entries {split(block)};
    for (auto i {entries.begin()}; i != entries.end() && !is_end(*i); ++i)
    {
      data.emplace_back(parse_header_entry(*i));
    }
    return {};
  }
}  // namespace fits
