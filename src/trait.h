/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef TRAIT_H
#define TRAIT_H

#include "unitbelief.h"

#include <QHash>
#include <QMap>
#include <QObject>
#include <QString>

class QSettings;

class Trait : public QObject {
    Q_OBJECT

private:
    QString m_name;
    bool m_inverted;
    int m_trait_id;

    struct skill_conflict{
        int skill_id;
        int limit;
        bool gains_skill;
    };

    //! this map will hold the minimum_value -> string (e.g. level 76-90 of ANXIETY_PROPENSITY is "Is always tense and jittery")
    QMap<int, QString> m_level_string;
    //belief_id, limit
    QList<int> m_belief_conflicts;
    //skill_id, limit
    QHash<int,skill_conflict> m_skill_conflicts;
    //limit, message
    QMap<short,QString> m_special;
    //limits
    QList<int> m_limits;

public:
    Trait(int trait_id, QSettings &s, QObject *parent = 0);

    QString get_name() const {return m_name;}
    int id() const {return m_trait_id;}
    bool valued_inversely() const {return m_inverted;} //specifically when setting the drawn rating

    QString level_message(const short &val);
    QString skill_conflicts_msgs(const short &val);
    QString skill_conflict_msg(const short &skill_id, const short &val);

    QString belief_conficts_msgs(short raw_value, QList<UnitBelief> conflicting_beliefs);
    QString belief_conflicts_names();
    QString special_messages(const short &val);

    QList<int> get_conflicting_beliefs(){return m_belief_conflicts;}

    static QColor goal_color;
    static QColor belief_color;

    static QString inverted_message;
};

#endif

