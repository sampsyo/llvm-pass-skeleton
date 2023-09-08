# Define a module library called Skeleton.
add_library(Skeleton MODULE Skeleton.cpp)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(Skeleton PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

add_llvm_pass_plugin(SkeletonPass Skeleton.cpp)
