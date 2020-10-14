#include <string.h>
#include <iostream>
#include <string>
#include <optional>
#include <map>
#include <vector>
#define HAVE_STDINT_H 
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>


#include "node.hpp"
#include "nodes_manager.hpp"

netsnmp_session* openSession(const char* hostIP,const char* communityName)
{
    netsnmp_session session, *ss;
    snmp_sess_init( &session );
    session.peername = strdup(hostIP);
    session.version = SNMP_VERSION_1;
    session.community = reinterpret_cast<unsigned char*>(const_cast<char*>(communityName));
    session.community_len = strlen(communityName);

    SOCK_STARTUP;
    ss = snmp_open(&session);                     /* establish the session */

    if (!ss) {
      snmp_sess_perror("ack", &session);
      SOCK_CLEANUP;
      return nullptr;
    }

    return ss;
}

std::optional<netsnmp_pdu *> getParameter(const char* requestedOid, netsnmp_session* currentSession)
{
    netsnmp_pdu *response = nullptr;
    netsnmp_pdu *pdu;
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;
    pdu = snmp_pdu_create(SNMP_MSG_GET);
    anOID_len = MAX_OID_LEN;
    if (!snmp_parse_oid(requestedOid, anOID, &anOID_len)) {
      snmp_perror(requestedOid);
      SOCK_CLEANUP;
      exit(1);
    }

    snmp_add_null_var(pdu, anOID, anOID_len);
  
    /*
     * Send the Request out.
     */
    int status = snmp_synch_response(currentSession, pdu, &response);
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
        return response;
    else
      if (status == STAT_SUCCESS)
        fprintf(stderr, "Error in packet\nReason: %s\n",
                snmp_errstring(response->errstat));
      else if (status == STAT_TIMEOUT)
        fprintf(stderr, "Timeout: No response.\n");
      else
        snmp_sess_perror("snmpdemoapp", currentSession);
      return std::nullopt;
}

void printResponse(const std::optional<netsnmp_pdu*> response)
{
    netsnmp_variable_list *vars;
    int count = 0;
    if (response) {
      for (vars = response.value()->variables; vars; vars = vars->next_variable)
      {
        if (vars->type == ASN_OCTET_STR)
        {
          std::cout << "Received a string: \"" << std::endl;
          std::cout << *(vars->val.string) <<"\"" << std::endl;
        }
        else if (vars->type == ASN_INTEGER)
        {
          std::cout << "Received an integer: \"";
          std::cout << *(vars->val.integer) <<"\"" << std::endl;
        }
        else
          std::cout << "Received a data type that hasn't been implemented yet." << std::endl;
      }
    } 
}

int main(int argc, char ** argv)
{
    std::optional<netsnmp_pdu*> response;
    Type PDU;
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1", "Temperature");
    Node firstPDU(PDU, "192.168.1.200", "public");
    Node secondPDU(PDU, "192.168.1.201", "public");
    NodesManager manager;
    manager.addNode(firstPDU);
    manager.addNode(secondPDU);
    manager.start();
    /*
    std::map<std::string, std::string> hosts; //List of hosts to be fetched. A host is defined by its ip address and a community name used to log in.
    hosts["192.168.1.200"] = "public";
    hosts["192.168.1.201"] = "public";
    std::vector<char*> parameters; //List of OIDS to be fetched.
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.5.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.6.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.7.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.8.3.1.5.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.8.3.1.5.2");

    init_snmp("snmpdemoapp");

    for (const auto& pdu : hosts)
    {
      auto ss = openSession(pdu.first.c_str(),pdu.second.data());
      if (ss)
      {
        for (const auto& parameter : parameters)
        {
          response = getParameter(parameter, ss);
          if (response)
          {
            printResponse(response);
            snmp_free_pdu(response.value());
          }
        }
      }
      snmp_close(ss);
      SOCK_CLEANUP;
    }*/

    return (0);
}
