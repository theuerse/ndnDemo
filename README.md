
Basic ndn-Producer / -Consumer(s)


Requirements:
	ndn-cxx version 0.3.4 (http://named-data.net/)
	nfd	version 0.3.4 (http://named-data.net/)


Scenarios:
	Samuel L.  (using placeholder text from http://slipsum.com/ :-D )
		nfd-start
		./producer --prefix /ndn101 --document-root ../res --data-size 100
		./consumer --name /ndn101/samuel.txt/0

