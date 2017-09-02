from bs4 import BeautifulSoup
import lxml.html
from pc import download
"""
broken_html = '<ul class=country><li>Area<li>Population</ul>'
soup = BeautifulSoup(broken_html,'html.parser')
fixed_html = soup.prettify()
print fixed_html

ul = soup.find('ul',attrs={'class':'country'})
print ul
li = soup.find('li')
print li
"""
"""
url = 'http://www.wondersoft.cn'
html = download(url)
soup = BeautifulSoup(html,'html.parser')
head = soup.find('head')
#print head
links = head.find_all('link')
print links
"""

"""
broken_html = '<ul class=country><li>Area<li>Population</ul>'
tree = lxml.html.fromstring(broken_html)
fixed_html = lxml.html.tostring(tree,True)
print fixed_html
"""


from bs4 import BeautifulSoup
import requests
import random

def get_ip_list(url, headers):
    web_data = requests.get(url, headers=headers)
    soup = BeautifulSoup(web_data.text, 'lxml')
    ips = soup.find_all('tr')
    ip_list = []
    for i in range(1, len(ips)):
        ip_info = ips[i]
        tds = ip_info.find_all('td')
        ip_list.append(tds[1].text + ':' + tds[2].text)
    return ip_list

def get_random_ip(ip_list):
    proxy_list = []
    for ip in ip_list:
        proxy_list.append('http://' + ip)
    proxy_ip = random.choice(proxy_list)
    proxies = {'http': proxy_ip}
    return proxies

if __name__ == '__main__':
    url = 'http://www.xicidaili.com/nn/'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36'
    }
    ip_list = get_ip_list(url, headers=headers)
    #proxies = get_random_ip(ip_list)
    #print(proxies)
    print len(ip_list)
    for ip in ip_list:
        print ip