# TKTK delete
add_library(SkeletonLib MODULE
    # List your source files here.
    Skeleton.cpp
)

# TKTK delete
# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on macOS.
if(APPLE)
    set_target_properties(SkeletonLib PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

add_llvm_pass_plugin(SkeletonPass Skeleton.cpp)
