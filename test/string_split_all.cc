/**
 * @file split_string_by_string.cc
 * @brief 测试使用 SIMD 指令加速字符串分割
 * 多字符分割字符串性能结论：
 * 1、在字符串比较长的情况下，SIMD 指令有最佳性能
 * 2、这里的测试，构造 string_view 和加入到结果集合里也消耗非常多的时间，在注释掉这两操作之后，长文本分割性能数据：

not simd cost_ms:242
not simd V2 cost_ms:174
simd cost_ms:84

在把这两操作加回来后的性能数据

not simd cost_ms:471
not simd V2 cost_ms:387
simd cost_ms:290

  * 3、从评测数据看，SIMD 指令在处理分隔符有多个字符的字符串分割时，性能最佳，性能差达到1倍以上
 */
#pragma once
#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>

// 不使用 SIMD，使用标准库的查找，是性能最差的方式
std::vector<std::string_view> SplitString(std::string_view input, std::string_view delimiters) {
  if (delimiters.empty()) {
    return {input};
  }
  std::vector<std::string_view> tokens;
  std::string_view::size_type token_start = input.find_first_not_of(delimiters, 0);
  std::string_view::size_type token_end = input.find_first_of(delimiters, token_start);
  while (token_start != std::string_view::npos || token_end != std::string_view::npos) {
    tokens.emplace_back(input.substr(token_start, token_end - token_start));
    token_start = input.find_first_not_of(delimiters, token_end);
    token_end = input.find_first_of(delimiters, token_start);
  }
  return tokens;
}

// 不使用 SIMD，使用遍历，是非 SIMD 模式下性能最好的方式 [多个分隔符]
std::vector<std::string_view> SplitStringV2(std::string_view input, std::string_view delimiters) {
  if (delimiters.empty()) {
    return {input};
  }
  std::vector<std::string_view> tokens;
  const char* token_start = input.data();
  const char* p = token_start;
  const char* end_pos = input.data() + input.size();
  for (; p != end_pos; ++p) {
    bool match_delimiter = false;
    for (auto delimiter : delimiters) {
      if (*p == delimiter) {
        match_delimiter = true;
        break;
      }
    }
    if (match_delimiter) {
      if (p > token_start) {
        tokens.emplace_back(token_start, p - token_start);
      }
      token_start = p + 1;
      continue;
    }
  }
  if (p > token_start) {
    tokens.emplace_back(token_start, p - token_start);
  }
  return tokens;
}

std::vector<std::string> StringSplitHydraRaw(const std::string& sData, const std::string& sDelim, std::vector<std::string>& vItems) {
    vItems.clear();

    std::string::size_type bpos = 0;
    std::string::size_type epos = 0;
    std::string::size_type nlen = sDelim.size();
    while ((epos=sData.find(sDelim, epos)) != std::string::npos)
    {
        vItems.push_back(sData.substr(bpos, epos-bpos));
        epos += nlen;
        bpos = epos;
    }

    vItems.push_back(sData.substr(bpos, sData.size()-bpos));

    return vItems;
}

// 这个写的是最优秀的
std::vector<std::string_view> StringSplitHydra(const std::string_view& sData, const std::string_view& sDelim) {
    std::vector<std::string_view> vItems;

    std::string_view::size_type bpos = 0;
    std::string_view::size_type epos = 0;
    std::string_view::size_type nlen = sDelim.size();
    while ((epos=sData.find(sDelim, epos)) != std::string_view::npos)
    {
        vItems.emplace_back(sData.substr(bpos, epos-bpos));
        epos += nlen;
        bpos = epos;
    }

    vItems.emplace_back(sData.substr(bpos, sData.size()-bpos));

    return vItems;
}

std::vector<std::string_view> SplitStringChar(const std::string_view& input, const std::string_view& delimiter) {
  // std::vector<std::string_view> tokens;
  // size_t token_start = 0;
  // while (token_start < input.size()) {
  //   auto token_end = input.find_first_of(delimiter, token_start);
  //   if (token_end > token_start) {
  //     if (token_end == std::string_view::npos) {
  //       token_end = input.size();
  //     }
  //     tokens.emplace_back(input.substr(token_start, token_end - token_start));
  //   }
  //   if (token_end == input.size()) {
  //     break;
  //   }
  //   token_start = token_end + 1;
  // }
  // return tokens;
  std::vector<std::string_view> tokens;
  size_t token_start = 0;
  std::string_view::size_type nlen = delimiter.size();
  while (token_start < input.size()) {
    auto token_end = input.find_first_of(delimiter, token_start);
    if (token_end >= token_start) {
      tokens.emplace_back(input.substr(token_start, token_end - token_start));
    }
    if (token_end == std::string_view::npos) {
      break;
    }
    token_start = token_end + nlen;
  }
  return tokens;
}

// std::find只支持单字符
// std::vector<std::string_view> SplitStringV4(const std::string_view& input, const std::string_view& delimiter) {
//     std::vector<std::string_view> tokens;
//     // tokens.reserve(input.size());
//     auto token_start = input.begin();
//     while (token_start != input.end()) {
//         auto token_end = std::find(token_start, input.end(), delimiter);
//         if (token_end > token_start) {
//           tokens.emplace_back(token_start, token_end - token_start);
//         }
//         if (token_end == input.end()) {
//           break;
//         }
//         token_start = token_end + 1;
//     }

//     return tokens;

// } 

// 使用 SIMD 指令，在长文本下，是性能最佳的实现
std::vector<std::string_view> SplitStringWithSimd256(std::string_view input, std::string_view delimiters) {
  if (delimiters.empty()) {
    return {input};
  }

  if (input.size() < 32) {
    return SplitStringV2(input, delimiters);
  }

  std::vector<std::string_view> tokens;
  uint32_t end_pos = input.size() >> 5 << 5;
  const char* p = input.data();
  const char* end = p + end_pos;
  uint32_t last_lead_zero = 0;  // 上一轮256bit（32个字符）处理后剩下的未拷贝进结果集的字符串个数
  while (p < end) {
    __m256i cmp_a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));  // 32个字符加载进内存
    __m256i cmp_result_a = _mm256_cmpeq_epi8(cmp_a, _mm256_set1_epi8(delimiters[0]));

    for (int i = 1; i != delimiters.size(); ++i) {
      __m256i cmp_result_b = _mm256_cmpeq_epi8(cmp_a, _mm256_set1_epi8(delimiters[i]));
      cmp_result_a = _mm256_or_si256(cmp_result_a, cmp_result_b);
    }
    uint32_t mask = _mm256_movemask_epi8(cmp_result_a);
    if (mask == 0) {
      last_lead_zero += 32;
      p += 32;
      continue;
    }

    // 记录本次的头部0个数，注：mask的序和字符串序是相反的，所以这里头部的0对应字符串尾部的不匹配字符
    uint32_t lead_zero = __builtin_clz(mask);

    // 补上一次未拷贝的字符串
    uint32_t tail_zero = __builtin_ctz(mask);
    if (last_lead_zero != 0 || tail_zero != 0) {
      tokens.emplace_back(p - last_lead_zero, last_lead_zero + tail_zero);
    }
    mask >>= (tail_zero + 1);
    p += tail_zero + 1;

    // 补完，继续处理
    while (mask != 0) {
      uint32_t tail_zero = __builtin_ctz(mask);
      if (tail_zero != 0) {
        tokens.emplace_back(p, tail_zero);
      }
      mask >>= (tail_zero + 1);
      p += tail_zero + 1;
    }

    last_lead_zero = lead_zero;
    p += lead_zero;
  }

  // 256 bit（32字节） 对齐之后剩下的部分
  const char* token_start = input.data() + end_pos - last_lead_zero;
  const char* pp = token_start;
  const char* sentence_end = input.data() + input.size();
  for (; pp != sentence_end; ++pp) {
    bool match_delimiter = false;
    for (auto delimiter : delimiters) {
      if (*pp == delimiter) {
        match_delimiter = true;
        break;
      }
    }
    if (match_delimiter) {
      if (pp > token_start) {
        tokens.emplace_back(token_start, pp - token_start);
      }
      token_start = pp + 1;
      continue;
    }
  }
  if (pp > token_start) {
    tokens.emplace_back(token_start, pp - token_start);
  }
  return tokens;
}


int main() {
  std::vector<std::string_view> sentences;
  //  sentences.emplace_back(",  ,,,,,,,");
  // sentences.emplace_back(",, ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,");
  // sentences.emplace_back(",,, ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,");
  // sentences.emplace_back("1111111111");
  // sentences.emplace_back("1111111111111111111111111111111111111");
  // sentences.emplace_back("11 1111111111111   11111111111111111111111 ,11");
  //  sentences.emplace_back("11 11 11,111,111,111,111,1,1,1,,1,11  11111111111111,1111111111");
  sentences.emplace_back(
      "11 11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11 11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,1111111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1111111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "11,11,11,111,111,111,111,1,1,1,,1,11,1,1111111111111,1,1,11111111,"
      "111111111111111111111111111111111111111111,111111111");

  // SplitString
  {
    auto start_commit = std::chrono::steady_clock::now().time_since_epoch();
    for (int i = 0; i != 10000; ++i) {
      for (const std::string_view& item : sentences) {
        SplitString(item, " \t,");
      }
    }
    auto end_commit = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "not simd cost_ms:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_commit - start_commit).count() 
              << std::endl;
  }

  // SplitStringV2
  {
    // 单元测试
    for (const std::string_view& item : sentences) {
      auto output_1 = SplitString(item, ",\t ");
      auto output_2 = SplitStringV2(item, ",\t ");
      for (int i = 0; i != output_1.size(); ++i) {
        if (output_1[i] != output_2[i]) {
          std::cout << "SplitStringV2 has error" << std::endl;
          std::cout << i << ":" << output_1[i] << std::endl;
          std::cout << i << ":" << output_2[i] << std::endl;
        }
      }
    }

    auto start_commit = std::chrono::steady_clock::now().time_since_epoch();
    for (int i = 0; i != 10000; ++i) {
      for (const std::string_view& item : sentences) {
        SplitStringV2(item, " \t,");
      }
    }
    auto end_commit = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "not simd V2 cost_ms:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_commit - start_commit).count() 
              << std::endl;
  }

  // SplitStringHydra
  {
    // 单元测试
    for (const std::string_view& item : sentences) {
      auto output_1 = SplitStringChar(item, ",");
      auto output_2 = StringSplitHydra(item, ",");
      if (output_1.size() != output_2.size()) {
        std::cout << "o1 size: " << output_1.size() << ",o2 size: " << output_2.size() << std::endl;
        // break;
      }
      for (int i = 0; i != output_1.size(); ++i) {
        if (output_1[i] != output_2[i]) {
          std::cout << "SplitStringV2 has error" << std::endl;
          std::cout << i << ":" << output_1[i] << std::endl;
          std::cout << i << ":" << output_2[i] << std::endl;
          // break;
          break;
        }
      }
    }

    auto start_commit = std::chrono::steady_clock::now().time_since_epoch();
    for (int i = 0; i != 10000; ++i) {
      for (const std::string_view& item : sentences) {
        SplitStringChar(item, ",");
      }
    }
    auto end_commit = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "hydra cost_ms:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_commit - start_commit).count() 
              << std::endl;
  }

  // SplitStringWithSimd256
  {
    // 单元测试
    for (const std::string_view& item : sentences) {
      auto output_1 = SplitString(item, ",\t ");
      auto output_2 = SplitStringWithSimd256(item, ",\t ");
      for (int i = 0; i != output_1.size(); ++i) {
        if (output_1[i] != output_2[i]) {
          std::cout << "SplitStringWithSimd256 has error" << std::endl;
          std::cout << i << ":" << output_1[i] << std::endl;
          std::cout << i << ":" << output_2[i] << std::endl;
        }
      }
    }

    auto start_commit = std::chrono::steady_clock::now().time_since_epoch();
    for (int i = 0; i != 10000; ++i) {
      for (const std::string_view& item : sentences) {
        SplitStringWithSimd256(item, " \t,");
      }
    }
    auto end_commit = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "simd cost_ms:"
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_commit - start_commit).count() 
              << std::endl;
  }

  return 0;
}