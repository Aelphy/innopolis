 # coding=utf-8

import vk_api
import time
import random

### You need to install vk by the following command:
# pip install vk_api

login = ''
password = ''

vkapi = vk_api.VkApi(login, password, app_id=4855775, scope='messages')
vkapi.authorization()

friends = vkapi.method('friends.get', {'fields' : 'name'})['items']

friends_count = len(friends)
start = 457

for i in range(start, friends_count):
    try:
        first_name = friends[i]['first_name']
        friend_id = friends[i]['id']

        message = u'Привет, {0}. Текст.'.format(first_name)

        vkapi.method('messages.send', {'user_id' : friend_id, 'message' : message})
        print('{0} out of {1}'.format(i + 1, friends_count))
    except Exception:
        print('retry {0}'.format(i))
        time.sleep(5)

        try:
            vkapi.method('messages.send', {'user_id' : friend_id, 'message' : message})
            print('{0} out of {1}'.format(i + 1, friends_count))
        except Exception as e:
            print('skiped {0} because of:'.format(i), e)
            pass
    finally:
        time.sleep(1.5 + random.uniform(0, 2))
