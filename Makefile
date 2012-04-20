CC=gcc
CCFLAGS=-g 
rm=rm
rm_flags=-f

FSRC=calc.l 
BSRC=calc.y
CSRC=calc.lex.c calc.yy.c 
EXCSRC=const.c global.c type.c
TARGET = calc

LEX=flex
LEX_FLAGS=
YYAC=bison
YYAC_FLAGS=-t
YYAC_FLAGS=--defines=calc.yy.h -t



$(TARGET) : $(CSRC)  $(EXCSRC)
	$(CC) $(CCFLAGS) -o $@ $^
%.lex.c : %.l
	$(LEX) $(LEX_FLAGS) -o $@  $<
%.yy.c : %.y
	$(YYAC) $(YYAC_FLAGS) -o $@ $<
clean :
	$(rm) -f $(CSRC) $(TARGET)
r:
	./$(TARGET) < input.c
