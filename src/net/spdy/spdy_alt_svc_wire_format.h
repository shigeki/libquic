// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file contains data structures and utility functions used for serializing
// and parsing alternative service header values, common to HTTP/1.1 header
// fields and HTTP/2 and QUIC ALTSVC frames.  See specification at
// https://tools.ietf.org/id/draft-ietf-httpbis-alt-svc-06.html

#ifndef NET_SPDY_SPDY_ALT_SVC_WIRE_FORMAT_H_
#define NET_SPDY_SPDY_ALT_SVC_WIRE_FORMAT_H_

#include <vector>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"

using base::StringPiece;

namespace net {

namespace test {
class SpdyAltSvcWireFormatPeer;
}  // namespace test

class NET_EXPORT_PRIVATE SpdyAltSvcWireFormat {
 public:
  struct NET_EXPORT_PRIVATE AlternativeService {
    std::string protocol_id;
    std::string host;
    // Default is 0: invalid port.
    uint16 port = 0;
    // Default is 0: unspecified version.
    uint16 version = 0;
    // Default is one day.
    uint32 max_age = 86400;
    // Default is always use.
    double p = 1.0;

    AlternativeService();
    AlternativeService(const std::string& protocol_id,
                       const std::string& host,
                       uint16 port,
                       uint16 version,
                       uint32 max_age,
                       double p);

    bool operator==(const AlternativeService& other) const {
      return protocol_id == other.protocol_id && host == other.host &&
             port == other.port && version == other.version &&
             max_age == other.max_age && p == other.p;
    }
  };
  typedef std::vector<AlternativeService> AlternativeServiceVector;

  friend class test::SpdyAltSvcWireFormatPeer;
  static bool ParseHeaderFieldValue(StringPiece value,
                                    AlternativeServiceVector* altsvc_vector);
  static std::string SerializeHeaderFieldValue(
      const AlternativeServiceVector& altsvc_vector);

 private:
  static void SkipWhiteSpace(StringPiece::const_iterator* c,
                             StringPiece::const_iterator end);
  static bool PercentDecode(StringPiece::const_iterator c,
                            StringPiece::const_iterator end,
                            std::string* output);
  static bool ParseAltAuthority(StringPiece::const_iterator c,
                                StringPiece::const_iterator end,
                                std::string* host,
                                uint16* port);
  static bool ParsePositiveInteger16(StringPiece::const_iterator c,
                                     StringPiece::const_iterator end,
                                     uint16* value);
  static bool ParsePositiveInteger32(StringPiece::const_iterator c,
                                     StringPiece::const_iterator end,
                                     uint32* value);
  static bool ParseProbability(StringPiece::const_iterator c,
                               StringPiece::const_iterator end,
                               double* p);
};

}  // namespace net

#endif  // NET_SPDY_SPDY_ALT_SVC_WIRE_FORMAT_H_
