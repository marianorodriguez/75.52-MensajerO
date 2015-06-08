add_library(mongoose mongoose.c)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMONGOOSE_ENABLE_THREADS") 
message ("Probando ${CMAKE_C_FLAGS}")
