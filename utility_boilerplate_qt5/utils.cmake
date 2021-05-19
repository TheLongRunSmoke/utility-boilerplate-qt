#----------------------------------
#
#   CMake utility scripts.
#
#----------------------------------

# to_lower_case(${arg} ret)
# Convert given arg to lower case characters and place it to ret.
function(to_lower_case ARG RET)
    set(LOWER_CASE "")
    string(TOLOWER ${ARG} LOWER_CASE)
    set(${RET} ${LOWER_CASE} PARENT_SCOPE)
endfunction()