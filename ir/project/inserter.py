import redis

class Inserter():
    def __init__(self):
        self.redis = redis.StrictRedis(host='localhost')

    def insert(self, key, doc_id, tf):
        if self.redis.hexists(key, doc_id):
            self.redis.hincrby(key, doc_id, tf)
        else:
            self.redis.hset(key, doc_id, tf)


    def clear_db(self):
        self.redis.flushdb()
