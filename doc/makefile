.SUFFIXES : .tex .ps .pdf .eps .png

SRC = swahili_dice.tex
TARGET = swahili_dice

.tex.dvi:
	latex $<

.dvi.ps ::
	dvips $*.dvi

.dvi.pdf ::
	dvipdf $*.dvi

all: ps pdf

ps: ${TARGET}.ps

pdf: ${TARGET}.pdf

#${TARGET}.ps: ${SRC}
#	latex ${SRC}
#	dvips ${TARGET}.dvi


md: ${TARGET}.md

${TARGET}.md: ${SRC}
	pandoc $? --to=markdown -o $@


neat:
	-rm -f *.aux *.log *~ *.dvi

clean: neat
	-rm -f ${TARGET}.pdf ${TARGET}.ps ${TARGET}.md
