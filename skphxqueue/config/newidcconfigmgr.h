#pragma once

#include "iFileFunc.h"


namespace skphxqueue {

namespace config {


template <typename ClientConfigType>
class NewIDCConfigMgr : public Comm::CIDCConfigManager<ClientConfigType> {
  public:
    NewIDCConfigMgr(const std::string &path)
            : Comm::CIDCConfigManager<ClientConfigType>(path.c_str()) {}
    virtual ~NewIDCConfigMgr() {}

    ClientConfigType * Release(const int idc) {

        ClientConfigType *conf = nullptr;
        assert( 0 == pthread_rwlock_wrlock( &this->m_tLock ) );
        {
            typename Comm::CIDCConfigManager<ClientConfigType>::ClientConfigMap::iterator
                    it = this->m_mapConfig.find(idc);
            if (this->m_mapConfig.end() != it) {
                conf = it->second;
                this->m_mapConfig.erase(it);
            }
        }
        assert( 0 == pthread_rwlock_unlock( &this->m_tLock ) );
        return conf;
    }
};


}  // namespace config

}  // namespace skphxqueue

