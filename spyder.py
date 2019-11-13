# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import re
import requests

def downloadPic(html,keyword):
  #  url = 'http://image.baidu.com/search/index?tn=baiduimage&ps=1&ct=201326592&lm=-1&cl=2&nc=1&ie=utf-8&word=%E5%9C%86'
  #  html = requests.get(url).text
    pic_url = re.findall('"objURL":"(.*?)",',html,re.S)
    
    i = 1
    print('find keyword:' + keyword + "'s pictures,downloading...")
    
    for each in pic_url:
        print('downloading' + str(i) + ' pictures,pic url is :' + str(each))
        
        try:
            pic = requests.get(each,timeout=10)
        except requests.exceptions.ConnectionError:
            print('error,can not download')
            continue
        
        dir = './images/' + keyword + '_' +str(i)+ '.jpg'
        fp = open(dir,'wb')
        fp.write(pic.content)
        fp.close()
        i += 1
        
if __name__ == '__main__':
    word = input('input keyword:')
    url = 'http://image.baidu.com/search/flip?tn=baiduimage&ie=utf-8&word=' + word + '&ct=201326592&v=fl'
    result = requests.get(url)
    downloadPic(result.text,word)
