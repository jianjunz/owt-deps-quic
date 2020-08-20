/*
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OWT_QUIC_TRANSPORT_QUIC_TRANSPORT_FACTORY_IMPL_H_
#define OWT_QUIC_TRANSPORT_QUIC_TRANSPORT_FACTORY_IMPL_H_

#include <memory>
#include <string>
#include <vector>
#include "owt/quic/export.h"
#include "owt/quic/quic_transport_factory.h"

namespace quic {
class QuicAlarmFactory;
class QuicConnectionHelperInterface;
class QuicClock;
class QuicRandom;
class QuicCompressedCertsCache;
class QuicCryptoServerConfig;
class ProofSource;
}  // namespace quic

namespace base {
class Thread;
class AtExitManager;
}  // namespace base

namespace owt {
namespace quic {

class OWT_EXPORT QuicTransportFactoryImpl : public QuicTransportFactory {
 public:
  QuicTransportFactoryImpl();
  ~QuicTransportFactoryImpl() override;
  // `accepted_origins` is removed at this time because ABI compatible issue.
  QuicTransportServerInterface* CreateQuicTransportServer(
      int port,
      const char* cert_path,
      const char* key_path) override;
  void ReleaseQuicTransportServer(
      const QuicTransportServerInterface* server) override;
  QuicTransportClientInterface* CreateQuicTransportClient(
      const char* url) override;
  QuicTransportClientInterface* CreateQuicTransportClient(
      const char* url,
      const QuicTransportClientInterface::Parameters& parameters) override;

 private:
  void Init();

  std::unique_ptr<base::Thread> io_thread_;
};

}  // namespace quic
}  // namespace owt

#endif