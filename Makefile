SRCS_BASELINE = baseline_main.c
SRCS_CUSTOM = custom_main.c

LIBSRCS_BASELINE = baseline_snapshot.c baseline_recovery.c open.c close.c set.c get.c
LIBSRCS_CUSTOM = custom_snapshot.c custom_recovery.c open.c close.c set.c get.c

TARG_BASELINE = kvs_baseline
TARG_CUSTOM = kvs_custom

CC = gcc
CFLAGS = -Wall -g -pg  # 프로파일링 활성화를 위해 -pg 추가
LIBS_BASELINE = -L. -lkvsb
LIBS_CUSTOM = -L. -lkvsc

OBJS_BASELINE = $(SRCS_BASELINE:.c=.o)
OBJS_CUSTOM = $(SRCS_CUSTOM:.c=.o)

LARS_BASELINE = libkvsb.a
LARS_CUSTOM = libkvsc.a

all: baseline custom

baseline: $(TARG_BASELINE)
custom: $(TARG_CUSTOM)

$(TARG_BASELINE): $(OBJS_BASELINE) $(LARS_BASELINE)
	$(CC) -o $(TARG_BASELINE) $(OBJS_BASELINE) $(LIBS_BASELINE) -pg

$(TARG_CUSTOM): $(OBJS_CUSTOM) $(LARS_CUSTOM)
	$(CC) -o $(TARG_CUSTOM) $(OBJS_CUSTOM) $(LIBS_CUSTOM) -pg

$(LARS_BASELINE): $(LIBSRCS_BASELINE:.c=.o)
	ar rs $(LARS_BASELINE) $^

$(LARS_CUSTOM): $(LIBSRCS_CUSTOM:.c=.o)
	ar rs $(LARS_CUSTOM) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean_custom:
	rm -f $(OBJS_CUSTOM) $(LIBSRCS_CUSTOM:.c=.o) $(LARS_CUSTOM) $(TARG_CUSTOM)

clean_baseline:
	rm -f $(OBJS_BASELINE) $(LIBSRCS_BASELINE:.c=.o) $(LARS_BASELINE) $(TARG_BASELINE)

clean: clean_custom clean_baseline
