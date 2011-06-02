lib_list := list
libraries := $(lib_list)
tests := tests

.PHONY: all $(libraries) $(tests)

all: $(tests)

$(tests) $(libraries):
	$(MAKE) --directory=$@ $(TARGET)

$(tests): $(libraries)
