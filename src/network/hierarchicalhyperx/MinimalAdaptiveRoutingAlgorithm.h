/*
 * Copyright 2016 Hewlett Packard Enterprise Development LP
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef NETWORK_HIERARCHICALHYPERX_MINIMALADAPTIVEROUTINGALGORITHM_H_
#define NETWORK_HIERARCHICALHYPERX_MINIMALADAPTIVEROUTINGALGORITHM_H_

#include <prim/prim.h>

#include <string>
#include <vector>

#include "event/Component.h"
#include "network/RoutingAlgorithm.h"
#include "router/Router.h"

namespace HierarchicalHyperX {

class MinimalAdaptiveRoutingAlgorithm : public RoutingAlgorithm {
 public:
  MinimalAdaptiveRoutingAlgorithm(
    const std::string& _name, const Component* _parent,
    u64 _latency, Router* _router, u32 _numVcs,
    const std::vector<u32>& _globalDimensionWidths,
    const std::vector<u32>& _globalDimensionWeights,
    const std::vector<u32>& _localDimensionWidths,
    const std::vector<u32>& _localDimensionWeights,
    u32 _concentration, u32 _globalLinksPerRouter, f64 _threshold_,
    u32 _localDeroute);

  ~MinimalAdaptiveRoutingAlgorithm();

 protected:
  void processRequest(
      Flit* _flit, RoutingAlgorithm::Response* _response) override;

 private:
  std::unordered_set<u32> routing(
      Flit* _flit, const std::vector<u32>& _destinationAddress);

  u32 findHighestPort(const std::unordered_map<u32, f64>& _portAvailability);

  void findPortAvailability(
     const std::vector<u32>& _diffDims,
     std::unordered_map<u32, f64>* _portAvailability,
     const std::vector<u32>& _destinationAddress, Flit* _flit);

  void ifAtLocalDst(
     Flit* _flit, std::unordered_set<u32>* _outputPorts,
     std::vector<u32>* _globalOutputPorts,
     const std::vector<u32>& diffGlobalDims);

  const u32 numVcs_;
  const std::vector<u32> globalDimWidths_;
  const std::vector<u32> globalDimWeights_;
  const std::vector<u32> localDimWidths_;
  const std::vector<u32> localDimWeights_;
  const u32 concentration_;
  const u32 globalLinksPerRouter_;
  const f64 threshold_;
  const u32 localDeroute_;
};

}  // namespace HierarchicalHyperX

#endif  // NETWORK_HIERARCHICALHYPERX_MINIMALADAPTIVEROUTINGALGORITHM_H_
