from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
import os

L = ['ACaslonPro-Regular.otf','AdobeArabic-Regular.otf','AdobeDevanagari-Regular.otf', 'AdobeFangsongStd-Regular.otf','AdobeHebrew-Regular.otf', 'AdobeHeitiStd-Regular.otf', 'AdobeKaitiStd-Regular.otf', 'AdobeMyungjoStd-Medium.otf', 'AdobeNaskh-Medium.otf','AGaramondPro-Regular.otf', 'arial.ttf', 'arialbd.ttf', 'bahnschrift.ttf', 'calibri.ttf', 'calibrib.ttf', 'cambria.ttc', 'cambriab.ttf', 'Candara.ttf', 'Candarab.ttf', 'ChaparralPro-Bold.otf', 'ChaparralPro-Regular.otf', 'consola.ttf', 'consolab.ttf', 'CooperBlackStd.otf', 'corbel.ttf', 'corbelb.ttf', 'ebrima.ttf', 'ebrimabd.ttf', 'framdit.ttf', 'Gabriola.ttf', 'georgia.ttf', 'georgiab.ttf',
'himalaya.ttf', 'HoboStd.otf',  
'Nirmala.ttf', 'NirmalaB.ttf','ntailu.ttf', 'ntailub.ttf', 'NuevaStd-Bold.otf',
'pala.ttf', 'palab.ttf', 'phagspa.ttf', 'phagspab.ttf',
'tahoma.ttf', 'tahomabd.ttf', 'taile.ttf', 'taileb.ttf', 'times.ttf', 'timesbd.ttf', 'trebuc.ttf', 'trebucbd.ttf', 'verdana.ttf', 'verdanab.ttf']

letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
os.chdir (os.path.dirname(os.path.dirname(__file__)) + '/src/Dataset')

lon_font = len(L)
lon_char = len(letter)

for j in range(7):
    for i in range(lon_font):
        font = ImageFont.truetype(L[i], 24)
        img = Image.new('RGB', (32, 32), color = 'white')
        draw = ImageDraw.Draw(img)
        draw.text((0, 0),letter[j],(0,0,0),font=font)
        #pixels = img.load() # create the pixel map
        img.save('image-' + str(j) + "-" + str(i + 1) + '.bmp', 'bmp')