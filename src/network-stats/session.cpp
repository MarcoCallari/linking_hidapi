#include "session.hpp"
#include <assert.h>

Session::Session(const std::string peername, const std::string community){
  m_request.version  = SNMP_VERSION_1;
  m_request.peername = strdup(peername.c_str());
  m_request.community = reinterpret_cast<unsigned char*>(strdup(community.c_str()));
  m_request.community_len = community.size();
}

void Session::request(const std::string oid){
  SOCK_STARTUP;
  m_activeSession = snmp_open(&m_request);
  if(!m_activeSession){
      SOCK_CLEANUP;
      assert(false); //Add error handling
    }
}
