
#include "qe/StringsDefinitions.h"
#include "qe/QDelegate.h"
#include "qe/SQFloat.h"
#include "qe/SQInteger.h"
#include "qe/Assertions.h"
#include "qe/LoggingUtilities.h"
#include "qe/QFileStream.h"
#include "qe/QTextStreamReader.h"
#include "qe/QBinaryStreamReader.h"
#include "qe/QHashtable.h"
#include "qe/SQStringHashProvider.h"
#include "qe/QStopwatch.h"
#include "qe/QVector3.h"
#include "qe/QVector4.h"
#include "qe/QVector2.h"
#include "qe/SQFile.h"
#include "qe/QTransformationMatrix.h"
#include "qe/QMatrix4x4.h"

using namespace Kinesis::QuimeraEngine::Tools::Math;
using namespace Kinesis::QuimeraEngine::Common;
using namespace Kinesis::QuimeraEngine::Common::DataTypes;
using namespace Kinesis::QuimeraEngine::System::IO::FileSystem;
using namespace Kinesis::QuimeraEngine::System::IO;
using namespace Kinesis::QuimeraEngine::Tools::Containers;
using namespace Kinesis::QuimeraEngine::System::Timing;
using namespace Kinesis::QuimeraEngine::Tools::Time;

typedef string_q QHashedString;
typedef QVector4 QColor;