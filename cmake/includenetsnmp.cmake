set (NET_SNMP_INCLUDE_DIR ${NET_SNMP_ROOT}/include)

# find_library (
#   NET_SNMP_RELEASE_LIB
#   netsnmp
#   ${NET_SNMP_ROOT}/lib
# )
find_library (
  NET_SNMP_DEBUG_LIB
  netsnmp
  ${NET_SNMP_ROOT}/lib
)
find_library (
  NET_SNMP_AGENT_DEBUG_LIB
  netsnmpagent
  ${NET_SNMP_ROOT}/lib
)
find_library (
  NET_SNMP_MIBS_DEBUG_LIB
  netsnmpmibs
  ${NET_SNMP_ROOT}/lib
)
find_library (
  NET_SNMP_TRAPD_DEBUG_LIB
  netsnmptrapd
  ${NET_SNMP_ROOT}/lib
)

# find_library (
#   ROOF_ROOFCORE_RELEASE_LIB
#   roofcore
#   ${NET_SNMP_ROOT}/li
# )
# find_library (
#   ROOF_ROOFCORE_DEBUG_LIB
#   roofcored
#   ${NET_SNMP_ROOT}/lib
# )

SET(NET_SNMP_LIBRARIES
  debug ${NET_SNMP_DEBUG_LIB}
  debug ${NET_SNMP_AGENT_DEBUG_LIB}
  debug ${NET_SNMP_MIBS_DEBUG_LIB}
  debug ${NET_SNMP_TRAPD_DEBUG_LIB}
  optimized ${NET_SNMP_DEBUG_LIB}
  optimized ${NET_SNMP_AGENT_DEBUG_LIB}
  optimized ${NET_SNMP_MIBS_DEBUG_LIB}
  optimized ${NET_SNMP_TRAPD_DEBUG_LIB}
  # debug ${}
  # optimized ${}
  # optimized ${}
)
