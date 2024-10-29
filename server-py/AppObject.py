class AppObject:
    app = None

    @classmethod
    def __initClass__(cls,app):
        cls.app=app
