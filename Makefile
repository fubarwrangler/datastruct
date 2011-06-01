lib_list := list
libraries := $(lib_list)
tests := tests

.PHONY: all $(libraries)

all: $(player)

$(tests) $(libraries):
	$(MAKE) --directory=$@ $(TARGET)

$(tests): $(libraries)

