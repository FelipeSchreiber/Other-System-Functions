# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# EEL270 - Computacao II - Turma 2017/1
# Prof. Marcelo Luiz Drumond Lanza
	
# $Author:$
# $Date:$
# $Log:$


CC = gcc
LD = gcc

CDFLAGS = -ansi -Wall -std=c99 -g -D DEBUGGING
CFLAGS = -ansi -Wall -std=c99
LFLAGS = -ansi -Wall

ROOT = /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP
ROOTTEST = /users/victor.oliveira/public/html/EEL270/2017-1/VRRO_AAP
#ROOT = ~/Desktop/Test

DIRECTORIESINSTALL = $(ROOT)/Binaries\
	$(ROOT)/Data/Cookies\
	$(ROOT)/CGIs\
	$(ROOT)/Html\
	$(ROOT)/CSS\
	$(ROOTTEST)/CGIs\
	$(ROOTTEST)/HTML\
	$(ROOTTEST)/CSS

DIRECTORIESDEINSTALL = $(ROOT)/Binaries\
	$(ROOT)/Data/Cookies\
	$(ROOT)/Data\
	$(ROOT)/CGIs\
	$(ROOT)/CSS\
	$(ROOT)/Html\
	$(ROOT)\
	$(ROOTTEST)/CGIs\
	$(ROOTTEST)/CSS\
	$(ROOTTEST)/HTML\
	$(ROOTTEST)

EXECS = vrroUml\
	test\
	maind

CGIS = vrroUmlMain.cgi\
	vrroUmlShowWebHelp.cgi\
	vrroUmlShowRequestRegistrationForm.cgi\
	vrroUmlShowRequestPasswordResetForm.cgi\
	vrroUmlShowLicense.cgi


TESTOBJS = vrroUmlTestProgram.o vrroUmlErrors.o vrroUmlFunctions.o vrroUmlRunNcursesInterface.o -lncurses
MAINOBJS = vrroUml.o vrroUmlErrors.o vrroUmlFunctions.o vrroUmlAddUser.o vrroUmlShowCliHelp.o vrroUmlUserInterface.o vrroUmlRejectInvite.o vrroUmlAcceptInvite.o vrroUmlGetUsers.o vrroUmlRequestRegistration.o 

CGIOBJS = vrroUmlErrors.o vrroUmlFunctions.o vrroUmlUserInterface.o
CGIMAINOBJS = vrroUmlCgiMain.o $(CGIOBJS)
CGIHELPOBJS = vrroUmlShowWebHelp.o $(CGIOBJS)
CGIREGISTEROBJS = vrroUmlShowRequestRegistrationForm.o $(CGIOBJS)
CGIPWDOBJS = vrroUmlShowRequestPasswordResetForm.o $(CGIOBJS)
CGILICENSEOBJS = vrroUmlShowLicense.o $(CGIOBJS)
CGILOGINOBJS = vrroUmlCgiLogin.o $(CGIOBJS)

ALLCGI = $(CGIMAINOBJS)\
	$(CGIREGISTEROBJS)\
	$(CGIPWDOBJS)\
	$(CGILICENSEOBJS)



.c.o:
	$(CC) $(CDFLAGS) -c $<

all: $(EXECS) $(CGIS)


install: createdirs vrroUml $(CGIS) 
	cp vrroUml $(ROOT)/Binaries/vrroUml
	cp ./../HTML/index_pt-br.html $(ROOT)/Html/index_pt-br.html
	cp ./../HTML/index_en-us.html $(ROOT)/Html/index_en-us.html
	cp ./../HTML/bg.png $(ROOT)/bg.png
	cp ./../HTML/style.css $(ROOT)/CSS/style.css
	cp ./../HTML/styleW3.css $(ROOT)/CSS/styleW3.css
	cp ./../HTML/index_pt-br.html $(ROOTTEST)/HTML/index_pt-br.html
	cp ./../HTML/index_en-us.html $(ROOTTEST)/HTML/index_en-us.html
	cp ./../HTML/bg.png $(ROOTTEST)/bg.png
	cp $(ROOT)/CGIs/vrroUmlMain.cgi $(ROOTTEST)/CGIs/vrroUmlMain.cgi
	cp $(ROOT)/CGIs/vrroUmlShowWebHelp.cgi $(ROOTTEST)/CGIs/vrroUmlShowWebHelp.cgi
	cp $(ROOT)/CGIs/vrroUmlShowRequestRegistrationForm.cgi $(ROOTTEST)/CGIs/vrroUmlShowRequestRegistrationForm.cgi
	cp $(ROOT)/CGIs/vrroUmlShowRequestPasswordResetForm.cgi $(ROOTTEST)/CGIs/vrroUmlShowRequestPasswordResetForm.cgi
	cp $(ROOT)/CGIs/vrroUmlShowLicense.cgi $(ROOTTEST)/CGIs/vrroUmlShowLicense.cgi
	cp ./../HTML/style.css $(ROOTTEST)/CSS/style.css
	cp ./../HTML/styleW3.css $(ROOTTEST)/CSS/styleW3.css
	rm -f /users/victor.oliveira/public/html/index.html
	cp ./../HTML/index.html /users/victor.oliveira/public/html/index.html
	
createdirs:
	mkdir -p $(DIRECTORIESINSTALL)

deinstall:
	rm -f $(DIRECTORIESDEINSTALL)/*
	rmdir $(DIRECTORIESDEINSTALL)

test: $(TESTOBJS)
	$(LD) $(LFLAGS) -o $@ $(TESTOBJS)

vrroUml: $(MAINOBJS)
	$(LD) $(LFLAGS) -o $@ $(MAINOBJS) -lcrypt

maind: $(MAINOBJS)
	$(LD) $(LFLAGS) -g -D DEBUGGING -o $@ $(MAINOBJS) -lcrypt	

vrroUmlMain.cgi: $(CGIMAINOBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGIMAINOBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi

vrroUmlShowWebHelp.cgi: $(CGIHELPOBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGIHELPOBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi

vrroUmlShowRequestRegistrationForm.cgi: $(CGIREGISTEROBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGIREGISTEROBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi

vrroUmlShowRequestPasswordResetForm.cgi: $(CGIPWDOBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGIPWDOBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi

vrroUmlShowLicense.cgi: $(CGILICENSEOBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGILICENSEOBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi	

vrroUmlCgiLogin.cgi: $(CGILOGINOBJS)
	$(LD) $(LFLAGS) -o /users/victor.oliveira/private/EEL270/2017-1/VRRO_AAP/CGIs/$@ $(CGILOGINOBJS) -lcrypt -lncurses -L./../Libraries -lmlcgi				

clean:
	rm -f *.o *.out *.exe $(EXECS) $(LIBS)		

#$RCSfile:$
