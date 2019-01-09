#ifndef analysis_CMS_SUS_17_009_h
#define analysis_CMS_SUS_17_009_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"

namespace MA5
{
class CMS_SUS_17_009 : public AnalyzerBase
{
  INIT_ANALYSIS(CMS_SUS_17_009,"CMS_SUS_17_009")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
};
}

#endif