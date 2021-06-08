# ----------------------------------
#
# CMake utility scripts.
#
# ----------------------------------

# to_lower_case(${arg} ret) Convert given arg to lower case characters and place it to ret.
function(to_lower_case ARG RET)
    set(LOWER_CASE "")
    string(TOLOWER ${ARG} LOWER_CASE)
    set(${RET}
        ${LOWER_CASE}
        PARENT_SCOPE
    )
endfunction()

# get_parent_dir(${arg} ret) Return absolute path to directory one level up from ARG.
function(get_parent_dir ARG RET)
    set(PARENT "")
    get_filename_component(PARENT ${ARG}/../ ABSOLUTE)
    set(${RET}
        ${PARENT}
        PARENT_SCOPE
    )
endfunction()
