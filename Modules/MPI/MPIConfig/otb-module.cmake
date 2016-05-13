set(DOCUMENTATION "OTB module template.")

# OTB_module() defines the module dependencies in ExternalTemplate
# ExternalTemplate depends on OTBCommon and OTBApplicationEngine
# The testing module in ExternalTemplate depends on OTBTestKernel
# and OTBCommandLine

# define the dependencies of the include module and the tests
otb_module(MPIConfig
  DEPENDS
    OTBMPI
    OTBCommon
    OTBApplicationEngine
  TEST_DEPENDS
    OTBMPIImageIO
    OTBTestKernel
    OTBCommandLine
  DESCRIPTION
    "${DOCUMENTATION}"
)
