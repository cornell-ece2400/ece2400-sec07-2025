add_library(ece2400-sec07-lib
    ece2400-stdlib.c
    selection-sort-int.c
)

function(add_pa_exec bin srcs)
  add_executable(${bin} ${srcs})
  target_link_libraries(${bin} PUBLIC
    ece2400-sec07-lib
    m # math
  )
endfunction()

add_pa_exec(selection-sort-int-adhoc selection-sort-int-adhoc.c)

function(add_pa_test bin srcs)
  add_pa_exec(${bin} ${srcs})
  add_test(NAME ${bin}
         COMMAND ${bin})
endfunction()
