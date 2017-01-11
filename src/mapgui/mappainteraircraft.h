/*****************************************************************************
* Copyright 2015-2017 Alexander Barthel albar965@mailbox.org
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef LITTLENAVMAP_MAPPAINTERAIRCRAFT_H
#define LITTLENAVMAP_MAPPAINTERAIRCRAFT_H

#include "mapgui/mappainter.h"

#include <QCache>

namespace Marble {
class GeoDataLineString;
}

namespace atools {
namespace fs {
namespace sc {
class SimConnectAircraft;
class SimConnectUserAircraft;
}

}

}

class MapWidget;

/*
 * Draws the simulator user aircraft and aircraft track
 */
class MapPainterAircraft :
  public MapPainter
{
  Q_DECLARE_TR_FUNCTIONS(MapPainter)

public:
  MapPainterAircraft(MapWidget *mapWidget, MapQuery *mapQuery, MapScale *mapScale);
  virtual ~MapPainterAircraft();

  virtual void render(PaintContext *context) override;

  enum AircraftType
  {
    AC_SMALL,
    AC_JET,
    AC_HELICOPTER
  };

  struct PixmapKey
  {
    bool operator==(const MapPainterAircraft::PixmapKey& other) const;

    AircraftType type;
    bool ground;
    bool user;
    int size;
  };

private:
  void paintAircraftTrack(const PaintContext *context);

  void paintUserAircraft(const PaintContext *context,
                         const atools::fs::sc::SimConnectUserAircraft& userAircraft, float x, float y);
  void paintAiAircraft(const PaintContext *context,
                       const atools::fs::sc::SimConnectAircraft& aiAircraft);

  void paintTextLabelUser(const PaintContext *context, float x, float y, int size,
                          const atools::fs::sc::SimConnectUserAircraft& aircraft);
  void paintTextLabelAi(const PaintContext *context, float x, float y, int size,
                        const atools::fs::sc::SimConnectAircraft& aircraft);
  void appendClimbSinkText(QStringList& texts, const atools::fs::sc::SimConnectAircraft& aircraft);
  void appendAtcText(QStringList& texts, const atools::fs::sc::SimConnectAircraft& aircraft,
                     bool registration, bool type, bool airline, bool flightnumber);
  void appendSpeedText(QStringList& texts, const atools::fs::sc::SimConnectAircraft& aircraft,
                       bool ias, bool gs);
  void climbSinkPointer(QString& upDown, const atools::fs::sc::SimConnectAircraft& aircraft);

  void paintWindPointer(const PaintContext *context, const atools::fs::sc::SimConnectUserAircraft& aircraft,
                        int x, int y);
  void paintTextLabelWind(const PaintContext *context, int x, int y, int size,
                          const atools::fs::sc::SimConnectUserAircraft& aircraft);

  const QPixmap *pixmapFromCache(const PixmapKey& key);
  const QPixmap *pixmapFromCache(const atools::fs::sc::SimConnectAircraft& ac, int size, bool user);

  /* Minimum length in pixel of a track segment to be drawn */
  static Q_DECL_CONSTEXPR int AIRCRAFT_TRACK_MIN_LINE_LENGTH = 5;

  static Q_DECL_CONSTEXPR int DISTANCE_CUT_OFF_AI_LIMIT = 500;

  static Q_DECL_CONSTEXPR int WIND_POINTER_SIZE = 40;

  /* Caches pixmaps generated from SVG graphics */
  QCache<PixmapKey, QPixmap> aircraftPixmaps;

};

#endif // LITTLENAVMAP_MAPPAINTERMARKAIRCRAFT_H
