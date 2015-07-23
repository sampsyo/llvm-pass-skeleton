add_library(SkeletonPass MODULE
    # List your source files here.
    Skeleton.cpp
)

set_target_properties(SkeletonPass PROPERTIES
    COMPILE_FLAGS "-std=c++11 -fno-rtti"
    LINK_FLAGS "-undefined dynamic_lookup"
)
