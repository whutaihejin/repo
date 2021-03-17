
#ifndef NAV_DEFS_H__
#define NAV_DEFS_H__

/*
Copyright 2020 Tencent
@author zadezhao@qq.com
@date   2018-11-09
@brief  nav constant & typedefs
*/

#include <stddef.h>  // for size_t
#define __STDC_LIMIT_MACROS
#include <stdint.h>  // for int32_t

//---some macros def
#ifdef __GNUC__
#define NAV_LIKELY_(expr) __builtin_expect(!!(expr), 1)
#define NAV_UNLIKELY_(expr) __builtin_expect(!!(expr), 0)
#define NAV_FUNC_ __PRETTY_FUNCTION__
#else
#define NAV_LIKELY_(expr) (expr)
#define NAV_UNLIKELY_(expr) ((expr))
#define NAV_FUNC_ __FUNCTION__
#endif  // __GNUC__

#ifdef NAV_ENABLE_ASSERT
#define NAV_ASSERT_(expr) \
  (NAV_LIKELY_(!!(expr)) ? ((void)0) : ::nav::assertFailed(#expr, NAV_FUNC_, __FILE__, __LINE__))
#else
#define NAV_ASSERT_(expr) ((void)0)
#endif  // NAV_ENABLE_ASSERT

namespace nav {
const size_t NAME_MAX_LEN = 64;
const size_t NAME_MAX_LEN_1 = NAME_MAX_LEN - 1;
const uint32_t BAD_ID32 = uint32_t(-1);
const uint64_t BAD_ID64 = uint64_t(-1);

//----------------- cost typedef & constants ----------------
typedef int32_t cost_t;
const cost_t BAD_COST = cost_t(-1);
const cost_t ZERO_COST = cost_t(0);

//----------------------- coordinate typedef ----------------
typedef int32_t coord_t;

// user must define this function if NAV_ENABLE_ASSERT is defined
void assertFailed(char const *expr, char const *fn, char const *file, long line);
}  // namespace nav

#endif  // NAV_DEFS_H__
﻿#ifndef NAV_UTILS_H__
#define NAV_UTILS_H__
/*
Copyright 2020 Tencent
@author zadezhao@qq.com
@date   2019-01-18
@brief  nav base utility file
*/
#include <string.h>    // for strncpy
#include <sys/time.h>  // for gettimeofday
#include <time.h>      // for strftime

#include <algorithm>  // for std::lower_bound
#include <istream>    // for std::istream
#include <ostream>    // for std::ostream
#include <string>     // for std::string
#include <unordered_map>
#include <vector>  // for std::vector

#include "navdefs.h"

namespace nav {
//----------- some free functions ------------------------------
class NavUtil {
 public:
  static const char *time2str(char *buf, size_t maxsize, time_t t, const char *format = NULL) {
    const char defaultFormat[] = "%Y-%m-%d %H:%M:%S";

    if (NULL == format) {
      format = defaultFormat;
    }

    struct tm tinfo;

    localtime_r(&t, &tinfo);

    strftime(buf, maxsize, format, &tinfo);

    return buf;
  }

  static long getDelay(const struct timeval &start) {
    struct timeval end;
    gettimeofday(&end, NULL);
    time_t diff = end.tv_sec - start.tv_sec;
    diff *= 1000000;
    diff += end.tv_usec - start.tv_usec;
    return long(diff);
  }

  static void copyName(char *name, const char *src) {
    if (NAV_UNLIKELY_(strncpy(name, src, NAME_MAX_LEN_1) == name + NAME_MAX_LEN_1)) {
      name[NAME_MAX_LEN - 1] = '\0';  // truncate
    }
  }

  static bool startsWith(const std::string &str, const char *prefix, size_t prefixSize) {
    return prefixSize <= str.length() && memcmp(str.data(), prefix, prefixSize) == 0;
  }

  static bool checkPrefix(const std::string &str, uint32_t id, size_t size,
                          const std::vector<char> &prefix) {
    if (size == 0U) {
      return false;
    }

    NAV_ASSERT_(prefix.size() > id + size);
    const char *begin = &prefix[id];

    for (size_t i = 0U; i != size; ++i) {
      NAV_ASSERT_(begin < begin + prefix.size());
      const size_t size = strlen(begin);

      if (startsWith(str, begin, size)) {
        return true;
      }

      begin += size + 1;
    }

    return false;
  }

  static uint64_t getSiweiId(const uint64_t txId) { return txId >> 1; }

  static uint64_t getTxId(const uint64_t siweiId, bool boDir) {
    if (boDir) {
      return siweiId << 1;
    }

    return (siweiId << 1) + 1;
  }
};
//----------- io for bytes ----------------------------------
template <class T>
std::ostream &writeBytes(std::ostream &out, const T &data, size_t size = sizeof(T)) {
  return out.write(reinterpret_cast<const char *>(&data), size);
}

template <class T>
std::istream &readBytes(std::istream &in, T &data, size_t size = sizeof(T)) {
  return in.read(reinterpret_cast<char *>(&data), size);
}
//----------- io for vector ----------------------------------
template <class T>
std::ostream &writeVector(std::ostream &out, const std::vector<T> &data) {
  const uint64_t size = data.size();
  writeBytes(out, size);

  if (size) {
    writeBytes(out, data[0], sizeof(data[0]) * size);
  }

  return out;
}

template <class T>
std::istream &readVector(std::istream &in, std::vector<T> &data) {
  uint64_t size = 0U;
  readBytes(in, size);

  if (size) {
    data.resize(size_t(size));
    readBytes(in, data[0], sizeof(data[0]) * size);
  }

  return in;
}

template <class InputIt, class Distance>
InputIt moveTo(InputIt itr, Distance n) {
  std::advance(itr, n);
  return itr;
}
//---------- bit set func&class -------------------------------
template <class IntType>
struct BitNum {
  enum { VALUE = sizeof(IntType) * 8 };
};

template <class IntType>
void resetBitSet(IntType *data, size_t size) {
  memset(data, 0, sizeof(IntType) * size);
}

template <class IntType>
void resetBitSet(IntType *data, size_t size, size_t pos) {
  const size_t idx = pos / BitNum<IntType>::VALUE;
  const size_t cnt = pos - idx * BitNum<IntType>::VALUE;
  NAV_ASSERT_(idx < size);
  data[idx] &= ~(static_cast<IntType>(1) << cnt);
}

template <class IntType>
void setBitSet(IntType *data, size_t size, size_t pos) {
  const size_t idx = pos / BitNum<IntType>::VALUE;
  const size_t cnt = pos - idx * BitNum<IntType>::VALUE;
  NAV_ASSERT_(idx < size);
  data[idx] |= (static_cast<IntType>(1) << cnt);
}

template <class IntType>
bool testBitSet(const IntType *data, size_t size, size_t pos) {
  const size_t idx = pos / BitNum<IntType>::VALUE;
  const size_t cnt = pos - idx * BitNum<IntType>::VALUE;
  NAV_ASSERT_(idx < size);
  return (data[idx] & (static_cast<IntType>(1) << cnt)) != static_cast<IntType>(0);
}

template <class IntType>
class DynBitSet {
  std::vector<IntType> bits_;

  static size_t wordSize(size_t size) {
    return size != 0 ? (size + BitNum<IntType>::VALUE - 1) / BitNum<IntType>::VALUE : 1;
  }

 public:
  explicit DynBitSet(size_t size) : bits_(wordSize(size)) {}

  size_t size() const { return bits_.size() * BitNum<IntType>::VALUE; }

  bool test(size_t pos) const {
    NAV_ASSERT_(!bits_.empty());
    return testBitSet(&bits_.front(), bits_.size(), pos);
  }

  bool operator[](size_t pos) const { return test(pos); }

  void resize(size_t size) { bits_.resize(wordSize(size)); }

  void reset(size_t pos) {
    NAV_ASSERT_(!bits_.empty());
    resetBitSet(&bits_.front(), bits_.size(), pos);
  }

  void resetAll() {
    NAV_ASSERT_(!bits_.empty());
    resetBitSet(&bits_.front(), bits_.size());
  }

  void set(size_t pos) {
    NAV_ASSERT_(!bits_.empty());
    setBitSet(&bits_.front(), bits_.size(), pos);
  }

  const std::vector<IntType> &data() const { return bits_; }

  std::ostream &write(std::ostream &out) const { return writeVector(out, bits_); }

  std::istream &read(std::istream &in) { return readVector(in, bits_); }
};

class NavIdIdx {
 public:
  uint64_t id;
  uint32_t idx;

  explicit NavIdIdx(uint64_t id = 0U, uint32_t idx = 0U) : id(id), idx(idx) {}

  bool operator<(const NavIdIdx &other) const { return id < other.id; }

  static uint32_t getIdx(const std::vector<NavIdIdx> &ididx, uint64_t id) {
    const NavIdIdx val(id, 0U);
    const auto itr = std::lower_bound(ididx.begin(), ididx.end(), val);
    return (itr != ididx.end() && !(val < *itr)) ? itr->idx : BAD_ID32;
  }
};
//------------------------------nav topo base -----------------------------
class LinkDescriptor {
 public:
  uint32_t src;
  uint32_t idx;

  explicit LinkDescriptor(uint32_t src = 0U, uint32_t idx = 0U) : src(src), idx(idx) {}

  bool operator==(const LinkDescriptor &other) const {
    return idx == other.idx && src == other.src;
  }

  bool operator!=(const LinkDescriptor &other) const { return !(*this == other); }
};

class OutLinkIterator : public std::iterator<std::random_access_iterator_tag, LinkDescriptor> {
 public:
  LinkDescriptor linkDesc;

  OutLinkIterator() {}

  explicit OutLinkIterator(LinkDescriptor linkDesc) : linkDesc(linkDesc) {}

  reference operator*() { return linkDesc; }

  pointer operator->() { return &linkDesc; }

  reference operator++() {
    ++linkDesc.idx;
    return linkDesc;
  }

  value_type operator++(int) {
    LinkDescriptor tmp(linkDesc);
    ++*this;
    return tmp;
  }

  reference operator--() {
    --linkDesc.idx;
    return linkDesc;
  }

  value_type operator--(int) {
    LinkDescriptor tmp(linkDesc);
    --*this;
    return tmp;
  }

  reference operator+=(difference_type off) {
    linkDesc.idx += off;
    return linkDesc;
  }

  value_type operator+(difference_type off) const {
    OutLinkIterator tmp(*this);
    return (tmp += off);
  }

  reference operator-=(difference_type off) { return (*this += -off); }

  value_type operator-(difference_type off) const {
    OutLinkIterator tmp(*this);
    return (tmp -= off);
  }

  difference_type operator-(const OutLinkIterator &other) const {
    return linkDesc.idx - other.linkDesc.idx;
  }

  bool operator==(const OutLinkIterator &other) const { return linkDesc == other.linkDesc; }

  bool operator!=(const OutLinkIterator &other) const { return !(*this == other); }
};

typedef std::pair<OutLinkIterator, OutLinkIterator> OutLinkRange;
typedef LinkDescriptor *InLinkIterator;
typedef std::pair<InLinkIterator, InLinkIterator> InLinkRange;

class LinkIterator : public std::iterator<std::forward_iterator_tag, LinkDescriptor> {
 public:
  const uint32_t *rowstart;
  uint32_t endOfNode;
  uint32_t totalLinks;
  LinkDescriptor curLink;

  LinkIterator() : rowstart(NULL), endOfNode(0U), totalLinks(0U) {}

  LinkIterator(const uint32_t *rowstart, uint32_t endOfNode, uint32_t totalLinks,
               LinkDescriptor curLink)
      : rowstart(rowstart), endOfNode(endOfNode), totalLinks(totalLinks), curLink(curLink) {}

  reference operator*() { return curLink; }

  pointer operator->() { return &curLink; }

  reference operator++() {
    ++curLink.idx;

    if (curLink.idx != totalLinks) {
      while (curLink.idx == endOfNode) {
        ++curLink.src;
        endOfNode = rowstart[curLink.src + 1];
      }
    }

    return curLink;
  }

  value_type operator++(int) {
    value_type tmp(curLink);
    ++*this;
    return tmp;
  }

  bool operator==(const LinkIterator &other) const { return curLink.idx == other.curLink.idx; }

  bool operator!=(const LinkIterator &other) const { return !(*this == other); }
};
typedef std::pair<LinkIterator, LinkIterator> LinkRange;

template <class RangeType>
bool empty(const RangeType &rt) {
  return rt.first == rt.second;
}
//------------------------------nav io base -------------------------------
enum NavMetaStatus {
  NM_OK = 0,
  NM_BAD = -1,
  NM_BAD_MAGIC = -2,
  NM_BAD_FORMAT_VERSION = -3,
  NM_BAD_DATA_VERSION = -4,
  NM_BAD_TOPO_VERSION = -5,
  NM_BAD_META_MATCHED = -6,
};

const uint64_t NM_MAGIC = 201502201750;
const uint64_t NM_DEFAULT_FORMAT = 20091109232301;  // from 20091109232301 to 20091109232399

class NavBaseMeta {
 public:
  uint64_t magic;
  uint64_t formatVersion;
  uint64_t dataVersion;
  uint64_t numLink;  // some NAV class may not need this field,such as NavTolls

  explicit NavBaseMeta(uint64_t formatVersion = 0U, uint64_t dataVersion = 0U,
                       uint64_t numLink = 0U)
      : magic(NM_MAGIC), formatVersion(formatVersion), dataVersion(dataVersion), numLink(numLink) {}

  NavMetaStatus checkMeta(uint64_t format) const {
    if (magic != NM_MAGIC) {
      return NM_BAD_MAGIC;
    } else {
      return formatVersion != format ? NM_BAD_FORMAT_VERSION : NM_OK;
    }
  }
};

class TopoMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  const static uint32_t ENABLE_INLINKS = 1U;

  uint64_t sizeTopoProp;
  uint64_t sizeNodeProp;
  uint64_t sizeLinkProp;
  uint64_t numNode;
  uint32_t enableInLink;
  uint32_t reserved;

  explicit TopoMeta(uint64_t sizeTopoProp = 0U, uint64_t sizeNodeProp = 0U,
                    uint64_t sizeLinkProp = 0U, uint64_t numNode = 0U, uint64_t numLink = 0U,
                    uint64_t dataVersion = 0U, bool fEnableInLink = false)
      : NavBaseMeta(FORMAT, dataVersion, numLink),
        sizeTopoProp(sizeTopoProp),
        sizeNodeProp(sizeNodeProp),
        sizeLinkProp(sizeLinkProp),
        numNode(numNode),
        enableInLink(0U),
        reserved(0U) {
    if (fEnableInLink) {
      setInLinks();
    }
  }

  void setInLinks() { enableInLink |= ENABLE_INLINKS; }

  void resetInLinks() { enableInLink &= ~ENABLE_INLINKS; }

  bool hasInLinks() const { return (enableInLink & ENABLE_INLINKS) != 0U; }
};

class CostMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numTurns;
  uint64_t topoVersion;  // from TopoMeta.dataversion
  char name[NAME_MAX_LEN];

  explicit CostMeta(uint64_t numTurns = 0U, uint64_t numLink = 0U, uint64_t dataVersion = 0U,
                    uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink), numTurns(numTurns), topoVersion(topoVersion) {
    memset(name, 0, sizeof(name));
  }
};

class RuleMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numRuleLinks;
  uint64_t numCond;
  uint64_t numDesc;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit RuleMeta(uint64_t numCond = 0U, uint64_t numRuleLinks = 0U, uint64_t numLink = 0U,
                    uint64_t numDesc = 0U, uint64_t dataVersion = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink),
        numRuleLinks(numRuleLinks),
        numCond(numCond),
        numDesc(numDesc),
        topoVersion(topoVersion) {}
};

class LimitMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numCond;
  uint64_t numLimitLink;
  uint64_t numCity;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit LimitMeta(uint64_t numLink = 0U, uint64_t numCond = 0U, uint64_t numLimitLink = 0U,
                     uint64_t numCity = 0U, uint64_t dataVersion = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink),
        numCond(numCond),
        numLimitLink(numLimitLink),
        numCity(numCity),
        topoVersion(topoVersion) {}
};

class NameMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numName;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit NameMeta(uint64_t numName = 0U, uint64_t numLink = 0U, uint64_t dataVersion = 0U,
                    uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink), numName(numName), topoVersion(topoVersion) {}
};

class CoordMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numCoord;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit CoordMeta(uint64_t numCoord = 0U, uint64_t numLink = 0U, uint64_t dataVersion = 0U,
                     uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink), numCoord(numCoord), topoVersion(topoVersion) {}
};

class AngleMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numAngle;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit AngleMeta(uint64_t numAngle = 0U, uint64_t dataVersion = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numAngle), numAngle(numAngle), topoVersion(topoVersion) {}
};

class TollsMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numNotTolls;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit TollsMeta(uint64_t numNotTolls = 0U, uint64_t dataVersion = 0U,
                     uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), numNotTolls(numNotTolls), topoVersion(topoVersion) {}
};

template <class MetaType>
NavMetaStatus checkTopoMatched(const MetaType &meta, uint64_t topoDataVersion,
                               uint64_t topoNumLink) {
  if (meta.dataVersion != topoDataVersion) {
    return NM_BAD_DATA_VERSION;
  } else {
    return meta.numLink != topoNumLink ? NM_BAD_META_MATCHED : NM_OK;
  }
}

class CostDiffFileMeta {
 public:
  const static size_t OFFSET_SIZE = 61;
  uint64_t magic;
  uint64_t format;
  uint32_t offsetSize;
  uint32_t reserved;
  uint64_t offset[OFFSET_SIZE];

  CostDiffFileMeta() : magic(NM_MAGIC), format(NM_DEFAULT_FORMAT), offsetSize(0U), reserved(0U) {
    memset(offset, 0, sizeof(offset));
  }
};

class InnerLinkMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numInLinks;
  uint64_t numOutNodes;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit InnerLinkMeta(uint64_t numInLinks = 0U, uint64_t numOutNodes = 0U,
                         uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, topoVersion, numInLinks),
        numInLinks(numInLinks),
        numOutNodes(numOutNodes),
        topoVersion(topoVersion) {}
};

class LightMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numLinks;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit LightMeta(uint64_t numLinks = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(NM_DEFAULT_FORMAT, topoVersion, numLinks),
        numLinks(numLinks),
        topoVersion(topoVersion) {}
};

class BrokenTurnsMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numNotTolls;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit BrokenTurnsMeta(uint64_t numNotTolls = 0U, uint64_t dataVersion = 0U,
                           uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), numNotTolls(numNotTolls), topoVersion(topoVersion) {}
};

class SameNodeMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t nodeSize;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit SameNodeMeta(uint64_t nodeSize = 0U, uint64_t dataVersion = 0U,
                        uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), nodeSize(nodeSize), topoVersion(topoVersion) {}
};

class SlopeMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t linkSize;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit SlopeMeta(uint64_t linkSize = 0U, uint64_t dataVersion = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), linkSize(linkSize), topoVersion(topoVersion) {}
};

class VoiceMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t linkSize;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit VoiceMeta(uint64_t linkSize = 0U, uint64_t dataVersion = 0U, uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), linkSize(linkSize), topoVersion(topoVersion) {}
};

class ExtendFieldMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t linkSize;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit ExtendFieldMeta(uint64_t linkSize = 0U, uint64_t dataVersion = 0U,
                           uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), linkSize(linkSize), topoVersion(topoVersion) {}
};

class SmallRoadMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t linkSize;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit SmallRoadMeta(uint64_t linkSize = 0U, uint64_t dataVersion = 0U,
                         uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, 0U), linkSize(linkSize), topoVersion(topoVersion) {}
};

class RuleTransMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numRuleLinks;
  uint64_t numCond;
  uint64_t numDesc;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit RuleTransMeta(uint64_t numCond = 0U, uint64_t numRuleLinks = 0U, uint64_t numLink = 0U,
                         uint64_t numDesc = 0U, uint64_t dataVersion = 0U,
                         uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink),
        numRuleLinks(numRuleLinks),
        numCond(numCond),
        numDesc(numDesc),
        topoVersion(topoVersion) {}
};

class ReplaceMultiRuleMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numRuleLinks;
  uint64_t numDesc;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit ReplaceMultiRuleMeta(uint64_t numRuleLinks = 0U, uint64_t numLink = 0U,
                                uint64_t numDesc = 0U, uint64_t dataVersion = 0U,
                                uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink),
        numRuleLinks(numRuleLinks),
        numDesc(numDesc),
        topoVersion(topoVersion) {}
};

class FillInnerLinkMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numLinks;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit FillInnerLinkMeta(uint64_t numLink = 0U, uint64_t dataVersion = 0U,
                             uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink), numLinks(numLink), topoVersion(topoVersion) {}
};

class LinkPropertiesMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint64_t numLinks;
  uint64_t topoVersion;  // from TopoMeta.dataversion

  explicit LinkPropertiesMeta(uint64_t numLink = 0U, uint64_t dataVersion = 0U,
                              uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, dataVersion, numLink), numLinks(numLink), topoVersion(topoVersion) {}
};

class RpElementConvertMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint32_t originNum;
  uint32_t newNum;

  explicit RpElementConvertMeta(uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, topoVersion, 0), originNum(0), newNum(0) {}
};

class TurnIdxNodeMeta : public NavBaseMeta {
 public:
  const static uint64_t FORMAT = NM_DEFAULT_FORMAT;
  uint32_t turnNum;

  explicit TurnIdxNodeMeta(uint64_t topoVersion = 0U)
      : NavBaseMeta(FORMAT, topoVersion, 0), turnNum(0) {}
};

}  // namespace nav

#endif  // NAV_UTILS_H__
