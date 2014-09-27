/* 
 * File:   SaveManager.h
 * Author: Rubén
 *
 * Created on 24 May 2013, 01:31
 */

#ifndef SAVEMANAGER_H
#define	SAVEMANAGER_H
 
class SaveManager {
public:
    static SaveManager* Instance();
    virtual ~SaveManager();

    void save(int n);
    int load();
private:
    SaveManager();
    SaveManager(const SaveManager& orig);
    SaveManager &operator= (const SaveManager &);
    static SaveManager* pinstance;

   
};

#endif	/* SAVEMANAGER_H */

