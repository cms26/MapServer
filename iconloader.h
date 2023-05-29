#ifndef ICONLOADER_H
#define ICONLOADER_H

#include<QIcon>

class IconLoader
{
public:
    static IconLoader& getInstance() {
        static IconLoader instance;
        return instance;
    }

    enum struct IconName {
        ZoomIn,
        ZoomOut,
        Globe
    };

    QIcon getIcon(const IconName& name) {return mIcons[name];}

private:
    IconLoader();
    ~IconLoader();
    std::map<IconName, QIcon> mIcons;
};

#endif // ICONLOADER_H
