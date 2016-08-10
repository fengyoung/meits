#ifndef _METIS_PLATFORM_WORKER_H 
#define _METIS_PLATFORM_WORKER_H 

#include <string>
using namespace std;
#include <stdint.h>
#include "ServConf.h"
#include "ThreadRWLock.h"
#include "JsonTransf.h"

#include "metis_nn.h"
using namespace metis_nn; 


#define _RESP_BUF_SIZE  (1024*1024*10)
#define _DEFAULT_TIMEOUT_MS		2000

#define _METIS_PLAT_SUCCESS		0
#define _METIS_PLAT_ISUPDATING  1
#define _METIS_PLAT_PARSEREQ_HEADER_FAIL	-2
#define _METIS_PLAT_PARSEREQ_FAIL	-3

#define _METIS_PLAT_EXCEPTION_OCCUR	-11
#define _METIS_PLAT_UNSUPPORT_CMD	-12

#define _METIS_PLAT_PUSHPATT_FAIL	-101
#define _METIS_PLAT_SETMODEL_FAIL	-102
#define _METIS_PLAT_GETMOEL_FAIL	-103
#define _METIS_PLAT_UPDATESTART_FAIL	-104


namespace metis_plat
{

class Worker 
{
public: 
	Worker(); 
	virtual ~Worker(); 

	void Init(ServConf& servConf); 
	

	virtual void WorkCore(Json::Value& jsonReq, Json::Value& jsonResp) = 0; 

	static bool SendCmd(const char* sHostPort, const char* sCmd, Json::Value& jsonReqBody, Json::Value& jsonResp, 
			const int32_t nLogId = 2016, const int32_t nSendTimeoutMs = _DEFAULT_TIMEOUT_MS, const int32_t nRecvTimeoutMs = _DEFAULT_TIMEOUT_MS); 
	
	static bool SendBinaryPatt(const char* sHostPort, Pattern* pPatt, Json::Value& jsonResp, 
			const int32_t nLogId = 2016, const int32_t nSendTimeoutMs = _DEFAULT_TIMEOUT_MS, const int32_t nRecvTimeoutMs = _DEFAULT_TIMEOUT_MS); 


protected:
	ServConf m_servConf; 
	static ThreadRWLock m_rwLock; 
};
	

}

#endif /* _METIS_PLATFORM_WORKER_H */

