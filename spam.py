 # coding=utf-8

import vk
import time
import random

### You need to create an application in vk. You can do it here:
### http://vk.com/dev

### You need to install vk by the following command:
# pip install vk

# insert here app id
app_id = '4855775'
user_email = ''
password = ''

vkapi = vk.API(app_id, user_email, password, scope = 'messages')

friends = vkapi.friends.get(fields = 'first_name')['items']

start = 0

for i in range(start, len(friends)):
    first_name = friends[i]['first_name']
    friend_id = friends[i]['id']

    message = u'Дорогой {0}. Тут сообщенице быть должно'.format(first_name)

    vkapi.messages.send(user_id = friend_id, message = message)
    print('{0} out of {1}'.format(i + 1, len(friends)))
    time.sleep(1 + random.uniform(0, 2))
