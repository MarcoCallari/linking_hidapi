#include <string.h>
#include <string>
#include <optional>
#include <map>
#include <vector>
#define HAVE_STDINT_H 
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

netsnmp_session* openSession(const char* hostIP,const char* communityName)
{
    /*
     * Initialize a "session" that defines who we're going to talk to
     */
    netsnmp_session session, *ss;
    snmp_sess_init( &session );                   /* set up defaults */
    session.peername = strdup(hostIP);

    /* set the SNMP version number */
    session.version = SNMP_VERSION_1;

    /* set the SNMPv1 community name used for authentication */
    session.community = reinterpret_cast<unsigned char*>(const_cast<char*>(communityName));
    session.community_len = strlen(communityName);

    /*
     * Open the session
     */
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
    /*
     * Create the PDU for the data for our request.
     */
    netsnmp_pdu *response;
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
    /*
     * Process the response.
     */
    netsnmp_variable_list *vars;
    int count = 0;
    if (response) {
      /*
       * SUCCESS: Print the result variables
       */

      for(vars = response.value()->variables; vars; vars = vars->next_variable)
        print_variable(vars->name, vars->name_length, vars);

      /* manipuate the information ourselves */
      for(vars = response.value()->variables; vars; vars = vars->next_variable) {
        if (vars->type == ASN_OCTET_STR) {
          char *sp = (char *)malloc(1 + vars->val_len);
          memcpy(sp, vars->val.string, vars->val_len);
          sp[vars->val_len] = '\0';
          printf("value #%d is a string: %s\n", count++, sp);
          free(sp);
        }
        else
          printf("value #%d is NOT a string! Ack!\n", count++);
      }
    } 
}

int main(int argc, char ** argv)
{
    int status;
    int count=1;
    std::optional<netsnmp_pdu*> response;
    std::map<const std::string, std::string> hosts; //List of hosts to be fetched. A host is defined by its ip address and a community name used to log in.
    hosts["192.168.1.200"] = "public";
    hosts["192.168.1.201"] = "public";
    std::vector<char*> parameters; //List of OIDS to be fetched.
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.5.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.6.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.6.3.1.7.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.8.3.1.5.1");
    parameters.push_back("1.3.6.1.4.1.318.1.1.26.8.3.1.5.2");

    /*
     * Initialize the SNMP library
     */
    init_snmp("snmpdemoapp");

    for (const auto pdu : hosts)
    {
      auto ss = openSession(pdu.first.c_str(),pdu.second.data());
      if (ss)
      {
        for (const auto parameter : parameters)
        {
          response = getParameter(parameter, ss);
          printResponse(response);
          if (response)
            snmp_free_pdu(response.value());
        }
      }
      snmp_close(ss);
      SOCK_CLEANUP;
    }

    return (0);
}
