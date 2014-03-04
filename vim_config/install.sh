#!/bin/bash

#install ctags
ctagsPath="ctags-5.8"
taglistPath="taglist"
tagList="~/.vim"
if [ ! -d "$ctagsPath" ]; then    
	wget http://prdownloads.sourceforge.net/ctags/ctags-5.8.tar.gz
	tar xf ctags-5.8.tar.gz 
fi
cd ctags-5.8
./configure
make
#sudo make install
cd ..

#check .vim folder
if [ ! -d "$tagLists" ]; then    
	mkdir ~/.vim
fi

#install taglist
if [ ! -d "$Path" ]; then    
	mkdir taglist
	cd taglist
	wget -O taglist.zip http://vim.sourceforge.net/scripts/download_script.php?src_id=19574
	unzip taglist.zip
	mv doc ~/.vim/
	mv plugin ~/.vim
fi
