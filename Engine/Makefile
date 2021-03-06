Options += -std=c++11 -Wall -fexceptions -O2

ifeq ($(OS), Windows_NT)
  CXX       = x86_64-w64-mingw32-g++
  obj       = obj_win
  Output    = bin/Gerber2pdf.exe
  Options  += -municode
  Resources = $(obj)/Resources/resource.res
else
  CXX       = g++
  obj       = obj_lin
  Output    = bin/Gerber2pdf
  Resources =
endif
#-------------------------------------------------------------------------------

Includes   = -ITools/Deflate
Includes  += -ITools/Gerber
Includes  += -ITools/Gerber/Gerber
Includes  += -ITools/PDF
Includes  += -ITools/PDF/afm
Includes  += -ITools/PDF/pdf
Includes  += -IToolbox/Cpp

Libraries  =
LibInclude =
#-------------------------------------------------------------------------------

Version = -DMAJOR_VERSION=1 -DMINOR_VERSION=6

Objects  = $(obj)/Tools/Deflate/JDeflate.o
Objects += $(obj)/Tools/Gerber/JGerber.o
Objects += $(obj)/Tools/Gerber/Gerber/GerberAperture.o
Objects += $(obj)/Tools/Gerber/Gerber/GerberLevel.o
Objects += $(obj)/Tools/Gerber/Gerber/GerberMacro.o
Objects += $(obj)/Tools/Gerber/Gerber/GerberRender.o
Objects += $(obj)/Tools/PDF/JPDF.o
Objects += $(obj)/Tools/PDF/afm/afmParser.o
Objects += $(obj)/Tools/PDF/pdf/pdfAnnotation.o
Objects += $(obj)/Tools/PDF/pdf/pdfArray.o
Objects += $(obj)/Tools/PDF/pdf/pdfBool.o
Objects += $(obj)/Tools/PDF/pdf/pdfCatalogue.o
Objects += $(obj)/Tools/PDF/pdf/pdfContents.o
Objects += $(obj)/Tools/PDF/pdf/pdfCustomFont.o
Objects += $(obj)/Tools/PDF/pdf/pdfDest.o
Objects += $(obj)/Tools/PDF/pdf/pdfDictionary.o
Objects += $(obj)/Tools/PDF/pdf/pdfFont.o
Objects += $(obj)/Tools/PDF/pdf/pdfFontDescriptor.o
Objects += $(obj)/Tools/PDF/pdf/pdfFontFile.o
Objects += $(obj)/Tools/PDF/pdf/pdfFontMetrics.o
Objects += $(obj)/Tools/PDF/pdf/pdfForm.o
Objects += $(obj)/Tools/PDF/pdf/pdfHyperlink.o
Objects += $(obj)/Tools/PDF/pdf/pdfImage.o
Objects += $(obj)/Tools/PDF/pdf/pdfIndirect.o
Objects += $(obj)/Tools/PDF/pdf/pdfJPEG.o
Objects += $(obj)/Tools/PDF/pdf/pdfName.o
Objects += $(obj)/Tools/PDF/pdf/pdfNumber.o
Objects += $(obj)/Tools/PDF/pdf/pdfObject.o
Objects += $(obj)/Tools/PDF/pdf/pdfOpaque.o
Objects += $(obj)/Tools/PDF/pdf/pdfOutlineItems.o
Objects += $(obj)/Tools/PDF/pdf/pdfOutlines.o
Objects += $(obj)/Tools/PDF/pdf/pdfPage.o
Objects += $(obj)/Tools/PDF/pdf/pdfPages.o
Objects += $(obj)/Tools/PDF/pdf/pdfPNG.o
Objects += $(obj)/Tools/PDF/pdf/pdfRectangle.o
Objects += $(obj)/Tools/PDF/pdf/pdfResources.o
Objects += $(obj)/Tools/PDF/pdf/pdfStream.o
Objects += $(obj)/Tools/PDF/pdf/pdfString.o
Objects += $(obj)/Tools/PDF/pdf/pdfType1Font.o
Objects += $(obj)/Tools/PDF/pdf/pdfType3Font.o
Objects += $(obj)/Toolbox/Cpp/General.o
Objects += $(obj)/Toolbox/Cpp/FileWrapper.o
Objects += $(obj)/Toolbox/Cpp/UTF_Converter.o
Objects += $(obj)/Engine.o

Headers  = Tools/Deflate/*.h
Headers += Tools/Gerber/*.h
Headers += Tools/Gerber/Gerber/*.h
Headers += Tools/PDF/*.h
Headers += Tools/PDF/afm/*.h
Headers += Tools/PDF/pdf/*.h
Headers += Toolbox/Cpp/*.h
Headers += *.h
#-------------------------------------------------------------------------------

.PHONY: clean all
.SECONDARY:

all: $(Output)

clean:
	rm -rf $(Output) $(obj)
#-------------------------------------------------------------------------------

# Binaries

$(Output): main.cpp main.h $(obj)/libEngine.a $(Resources)
	mkdir -p bin
	$(CXX) $(Options) $(Version) $(Includes) $< -s $(Resources) -L$(obj) -lEngine -o $@
#-------------------------------------------------------------------------------

# Libraries

$(obj)/libEngine.a: $(Objects)
	mkdir -p $(@D)
	ar -rcs $@ $(Objects)
#-------------------------------------------------------------------------------

# Objects

$(obj)/%.o: %.cpp $(Headers)
	mkdir -p $(@D)
	$(CXX) $(Options) $(Version) $(Defines) -c $(Includes) $< -o $@
#-------------------------------------------------------------------------------

# Resources

$(obj)/%.res: %.rc
	mkdir -p $(@D)
	windres.exe -J rc -O coff -i $< -o $@
#-------------------------------------------------------------------------------

