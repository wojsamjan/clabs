#
#  ... about 95 percent of software security bugs come from 
#  19 “common, well-understood” programming mistakes
#
#      Amit Yoran, 
#      the director of the National Cyber Security Division 
#      at the U.S. Department of Homeland Security
#
#  Common Vulnerabilities and Exposures (CVE) database 
#      www.cve.mitre.org
#  Open Source Vulnerability Database 
#      www.osdvb.org


CFLAGS = -Wall -g

csources = sin-01.c sin-02.c n.c
programs = $(csources:.c=)
data = text1.txt

.PHONY : clean

clean :
	rm -f *~ \#* *.o $(programs)
