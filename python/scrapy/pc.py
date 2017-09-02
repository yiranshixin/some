# -*- coding: <encoding name> -*-
import time
import  datetime
import re

import urllib2
import urlparse

def download(url):
    print "download: ",url
    try:
        html=urllib2.urlopen(url).read()
    except urllib2.URLError as e:
        print "download err: ",e.reason
        html=None
    return html

"""
html = download('http://www.cirrusgate.com/')
if html is not None:
    print html
"""

# n trys
def downloadTryTimes(url,tryTimes = 5):
    print "download: ",url
    try:
        html=urllib2.urlopen(url).read()
    except urllib2.URLError as e:
        print "download err: ",e.reason
        html=None
        if tryTimes > 0 :
            if hasattr(e,'code') and  500 <= e.code < 600 :
                time.sleep(1)
                tryTimes -= 1
                downloadTryTimes(url,tryTimes)
    return html

"""
html = downloadTryTimes('http://httpstat.us/500')
if html is not None:
    print html
"""

#agent
def downloadWithAgent(url, user_agent = "wswp", tryTimes = 5):
    print "download: ",url
    header = {"User-agent":user_agent}
    request = urllib2.Request(url, headers = header)
    try:
        html=urllib2.urlopen(request).read()
    except urllib2.URLError as e:
        print "download err: ",e.reason
        html=None
        if tryTimes > 0 :
            if hasattr(e,'code') and  500 <= e.code < 600 :
                time.sleep(1)
                tryTimes -= 1
                downloadWithAgent(request, user_agent, tryTimes)
    return html

"""
html = downloadWithAgent('http://www.meetup.com/')
if html is not None:
    print html
"""

def get_links(html):
    webpage_regex = re.compile('<a[^>]+href=["\'](.*?)["\']', re.IGNORECASE)
    return webpage_regex.findall(html)

#get all links
def link_crawler(seed_url, link_regex):
    crawl_queue = [seed_url]
    while crawl_queue:
        url = crawl_queue.pop()
        html = download(url)
        for link in get_links(html):
            if re.match(link_regex,link):
                crawl_queue.append(link)
"""
link_crawler('http://example.webscraping.com', ".*scure.*")
"""

#get all link by connect
def link_crawler_ref_parh(seed_url, link_regex_part):
    crawl_queue = [seed_url]
    while crawl_queue:
        url = crawl_queue.pop()
        html = download(url)
        for link in get_links(html):
            if re.match(link_regex_part,link):
                link = urlparse.urljoin(seed_url,link)
                crawl_queue.append(link)

"""
link_crawler_ref_parh('http://www.wondersoft.cn', "/(solution)")
"""

#remove overflow link
def link_crawler_ref_parh_no_overflow(seed_url, link_regex_part):
    crawl_queue = [seed_url]
    seen = set(crawl_queue)

    while crawl_queue:
        url = crawl_queue.pop()
        html = download(url)
        for link in get_links(html):
            if re.match(link_regex_part,link):
                link = urlparse.urljoin(seed_url,link)
                if link not in seen:
                    seen.add(link)
                    crawl_queue.append(link)

"""
link_crawler_ref_parh_no_overflow('http://www.wondersoft.cn', "/(solution)")
"""

#proxy
def download_with_proxy(url, user_agent = 'wswp', proxy = None, tryTimes = 5):
    print "download: ", url
    header = {'User-agent':user_agent}
    request = urllib2.Request(url, headers = header)

    opener = urllib2.build_opener()
    if proxy:
        proxy_params = {urlparse.urlparse(url).scheme:proxy}
        opener.add_handler(urllib2.ProxyHandler(proxy_params))
        try:
            html = opener.open(request).read()
        except urllib2.URLError as e:
            print 'download error: ', e.reason
            html = None
            if tryTimes > 0:
                if hasattr(e, 'code') and 500 <= e.code < 600:
                    html = download(url, user_agent, proxy, tryTimes-1)
        return html

#sleep for a timestamp
class Throttle:
    def __init__(self,delay):
        self.delay = delay
        self.domain = {}

    def wait(self,url):
        domain = urlparse.urlparse(url).netloc
        last_accessed = self.domain.get(domain)

        if self.delay > 0 and last_accessed is not None:
            sleep_secs = self.delay - (datetime.datetime.now() - last_accessed).seconds
            if sleep_secs > 0:
                time.sleep(sleep_secs)
        self.domain[domain] = datetime.datetime.now()

"""
throttle = Throttle(5)
url = r'http://www.wondersoft.cn'
for i in xrange(0,6):
    html = download(url)
    if html is not None:
        print html
    throttle.wait(url)
"""


