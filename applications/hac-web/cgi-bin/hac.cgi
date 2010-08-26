#!/bin/sh

HAC_WWW=/usr/www
HAC_WWW_CGI=$HAC_WWW/cgi-bin

HAC_HACCGI=$HAC_WWW_CGI/haccgi

RET_HTML=`$HAC_HACCGI`
echo $RET_HTML

exit 0
