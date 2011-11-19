// [TERMS&CONDITIONS]

#ifndef __QSIMPLECONFIGLOADER__
#define __QSIMPLECONFIGLOADER__

#include <string>
#include <vector>

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// A very simple machanism to read a list of values from a plain text file. Each entry must be in a separated line.
/// Text must be compound of 8-bits characteres.
/// </summary>
class QSimpleConfigLoader
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QSimpleConfigLoader();

	/// <summary>
	/// Constructor that uses a file path to initialize the loader.
	/// </summary>
	QSimpleConfigLoader(const std::string &strPath);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~QSimpleConfigLoader();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Retrieves an entry by its position.
    /// </summary>
    /// <param name="index">The entry position in the file.</param>
    /// <returns>
    /// The entry value.
    /// </returns>
    const std::string& operator[](const int &index) const;

    /// <summary>
    /// Uses the stored file path to find the text file to read entries from.
    /// Entries are stored in order of appearance.
    /// </summary>
    /// <returns>
    /// If there was no errors during entries loading, the it returns true.
    /// </returns>
    bool LoadEntries();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the text file path.
    /// </summary>
    /// <returns>
    /// The file path.
    /// </returns>
    std::string GetFilePath() const;

    /// <summary>
    /// Gets the text file path.
    /// </summary>
    /// <param name="strPath">The file path. It can be absolute or relative path.</param>
    void SetFilePath(const std::string &strPath);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The text file path.
    /// </summary>
    std::string _strPath;

    /// <summary>
    /// The entry list, in order of appearance.
    /// </summary>
    std::vector<std::string> _arConfigEntries;

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTESTCONFIGLOADER__
