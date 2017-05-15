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
#ifndef NETWORK_HIERARCHICALHYPERX_PROGRESSIVEADAPTIVERANDOMROUTINGALGORITHM_H_
#define NETWORK_HIERARCHICALHYPERX_PROGRESSIVEADAPTIVERANDOMROUTINGALGORITHM_H_

#include <prim/prim.h>

#include <string>
#include <vector>

#include "event/Component.h"
#include "network/RoutingAlgorithm.h"
#include "network/hierarchicalhyperx/ValiantRoutingAlgorithm.h"
#include "router/Router.h"

namespace HierarchicalHyperX {

class ProgressiveAdaptiveRandomRoutingAlgorithm : public
  ValiantRoutingAlgorithm {
 public:
  ProgressiveAdaptiveRandomRoutingAlgorithm(
    const std::string& _name, const Component* _parent,
    Router* _router, u64 _latency, u32 _baseVc, u32 _numVcs,
    const std::vector<u32>& _globalDimensionWidths,
    const std::vector<u32>& _globalDimensionWeights,
    const std::vector<u32>& _localDimensionWidths,
    const std::vector<u32>& _localDimensionWeights,
    u32 _concentration, u32 _globalLinksPerRouter,
    bool _randomGroup, f64 _bias, f64 _threshold);

  ~ProgressiveAdaptiveRandomRoutingAlgorithm();

 protected:
  void processRequest(
      Flit* _flit, RoutingAlgorithm::Response* _response) override;

 private:
  std::unordered_set<u32> routing(
      Flit* _flit, const std::vector<u32>& _destinationAddress) const;
  const f64 bias_;
  const f64 threshold_;
  static u32 numMinimalRoutes_;
  static u32 numNonMinimalRoutes_;
};

}  // namespace HierarchicalHyperX

#endif  // NETWORK_HIERARCHICALHYPERX_PROGRESSIVEADAPTIVERANDOMROUTINGALGORITHM_H_
