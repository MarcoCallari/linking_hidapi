#include "session.hpp"

Session::Session(const Node& node) : m_node{node}{
}

void Session::connectSession(){
  netsnmp_session session, *ss;
  snmp_sess_init( &session );
  session.version = SNMP_VERSION_1;
  auto ip = m_node.getIP();
  auto communityName = m_node.getCommunityName();
  session.peername = strdup(ip.c_str());
  session.community = reinterpret_cast<unsigned char*>(const_cast<char*>(communityName.c_str()));
  session.community_len = strlen(communityName.c_str());

  SOCK_STARTUP;
  m_session = snmp_open(&session);                     /* establish the session */

  if (!m_session) {
    snmp_sess_perror("ack", &session);
    SOCK_CLEANUP;
  }
}


Result Session::getAllOIDS(){
  connectSession();
  netsnmp_pdu *response = nullptr;
  netsnmp_pdu *pdu;
  oid anOID[MAX_OID_LEN];
  size_t anOID_len;

  auto oidsToFetch = m_node.getOIDS();
  for (const auto& requestedOid : oidsToFetch) {
    pdu = snmp_pdu_create(SNMP_MSG_GET);
    anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(requestedOid.first.c_str(), anOID, &anOID_len)) {
      snmp_perror(requestedOid.first.c_str());
      SOCK_CLEANUP;
      exit(1);
   }

    snmp_add_null_var(pdu, anOID, anOID_len);

    /*
     * Send the Request out.
     */
    int status = snmp_synch_response(m_session, pdu, &response);
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
      fprintf(stdout, "Ok");
    else
      if (status == STAT_SUCCESS)
        fprintf(stderr, "Error in packet\nReason: %s\n",
          snmp_errstring(response->errstat));
      else if (status == STAT_TIMEOUT)
        fprintf(stderr, "Timeout: No response.\n");
      else {
        std::string errorMsg = "Error when requesting " + requestedOid.second + " to host " + m_node.getIP();
        snmp_sess_perror(errorMsg.c_str(), m_session);
      }
  }
  return Result();
}
