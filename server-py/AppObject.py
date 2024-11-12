from typing import TYPE_CHECKING


class AppObject:
    if TYPE_CHECKING:
        from app import Application
        app : Application = None

    def finishEvent(event):
        pass

    @classmethod
    def __initClass__(cls,app):
        cls.app=app
