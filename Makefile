# Compiler settings
CXX = g++
# Set this to 1 when you move to the production server: make HAS_ONLOAD=1
HAS_ONLOAD ?= 0

# Flags
CXXFLAGS = -O3 -march=native -std=c++20 -pthread -Wall -Iinclude -DHAS_ONLOAD=$(HAS_ONLOAD)

# Linker flags: Only include onload if building for hardware
ifeq ($(HAS_ONLOAD), 1)
    LDFLAGS = -L/opt/onload/lib -lonload
else
    LDFLAGS = 
endif

# Targets
TARGET_ENGINE = hft_engine
TEST_BINS = test_cache_alignment test_packet_layout test_ring_buffer benchmark_latency
OBJECTS = obj/packet_pipeline.o obj/scheduler.o
obj/scheduler.o: src/scheduler.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Build all
all: $(TARGET_ENGINE) $(TEST_BINS)

# Compile object files
obj/packet_pipeline.o: src/packet_pipeline.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build Engine
$(TARGET_ENGINE): src/main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Build Benchmarks
$(TEST_BINS): % : tests/%.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf obj $(TARGET_ENGINE) $(TEST_BINS)
