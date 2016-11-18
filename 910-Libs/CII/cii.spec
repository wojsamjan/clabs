Summary: A library of handy interfaces: lists, tables, sets, sequences and more
Name: cii
Version: 1.1
Release: 1
License: GPL
Group: System Environment/Libraries
Source: ftp://ftp.cs.princeton.edu/pub/packages/cii/cii11.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot

%description 
C Interfaces and Implementations: Techniques for Creating Reusable Software 
(Addison-Wesley Professional Computing Series, 1997, ISBN 0-201-49841-3) 
advocates a design methodology based on interfaces and
their implementations, and it illustrates this methodology by describing
24 interfaces and their implementations in detail. These interfaces
include data structures, arithmetic, string processing, and concurrent
programming.
See http://www.cs.princeton.edu/software/cii/ for more info.

%prep
%setup -n cii -c

%build
export BUILDDIR=/var/tmp/%{name}-builddir
rm -rf $BUILDDIR
mkdir -p $BUILDDIR/include
cp -p include/*.h $BUILDDIR/include
make CC='cc -DMAXALIGN=4' AS='cc -c -x assembler-with-cpp -traditional'
make -n clean
#make -n CC='cc -DMAXALIGN=8' $BUILDDIR/memchk.o
#make -n clobber

%install
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"
mkdir -p $RPM_BUILD_ROOT/usr/lib/debug
mkdir -p $RPM_BUILD_ROOT/usr/lib/cii/1 
mkdir -p $RPM_BUILD_ROOT/usr/lib/cii/1/include
install -m 644 $BUILDDIR/libcii.a $RPM_BUILD_ROOT/usr/lib/cii/1
install -m 644 $BUILDDIR/include/*.h $RPM_BUILD_ROOT/usr/lib/cii/1/include

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"
[ -n "$BUILDDIR" -a "$BUILDDIR" != / ] && rm -rf "$BUILDDIR"

%post
/bin/ln -s /usr/lib/cii/1/libcii.a /usr/lib/libcii.a
/bin/ln -s /usr/lib/cii/1/include /usr/include/cii

%postun 
/bin/rm -f /usr/lib/libcii.a
/bin/rm -f /usr/include/cii

%files
%defattr(-,root,root)
%doc README CPYRIGHT packing.lst install.html history.html 
%doc src/*.c
%doc examples/*.[ch]
/usr/lib/cii/1/include/*.h
/usr/lib/cii/1/libcii.a


%changelog
* Mon Nov 27 2006 Wlodek Bzyl <matwb@univ.gda.pl>
- the first version
