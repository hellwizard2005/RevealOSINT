#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>

#include <json.hpp>

using nlohmann::json;

/**
 * class DataTable
 * brief Universal table structure based on nlohmann::json.
 *
 * Internally stores data as JSON:
 * - An array of rows
 * - Each row is a JSON object (key -> value)
 *
 * Example:
 * [
 *   { "name": "Alice", "age": 30 },
 *   { "name": "Bob",   "age": 25 }
 * ]
 */
class DataTable {
public:
    DataTable() = default;

    // --- Loaders (convert to JSON internally) ---
    bool loadFromJSON(const std::string& path);
    bool loadFromCSV(const std::string& path);
    bool loadFromHTML(const std::string& path);
    bool loadFromMarkdown(const std::string& path);
    bool loadFromXML(const std::string& path);
    bool loadFromXLSX(const std::string& path);

    // Unified loader
    bool loadFrom(const std::string& source, const std::string& format);

    // --- Saver ---
    bool saveToJSON(const std::string& path) const;

    // --- Export for visualization ---
    std::string toHTML() const;  ///< Convert JSON table into <table> HTML string

    // --- Cleaning ---
    void removeDuplicates();
    void removeNulls(const std::string& column);
    void filter(const std::string& column, const nlohmann::json& value);

    // --- Accessors ---
    nlohmann::json column(const std::string& name) const;
    int rowCount() const;

    // --- Direct access to JSON ---
    const nlohmann::json& raw() const { return m_data; }
    nlohmann::json& raw() { return m_data; }

private:
    nlohmann::json m_data; ///< Internal storage (array of objects)
};

//
// --- Analyzer ---
//
class Analyzer {
public:
    // Calculate arithmetic mean
    double mean(const json& column);

    // Calculate median
    double median(const json& column);

    // Calculate standard deviation
    double stddev(const json& column);

    // Moving average (window-based smoothing)
    std::vector<double> movingAverage(const json& column, int windowSize);

    // Correlation coefficient between two columns
    double correlation(const json& col1, const json& col2);

    // Detect anomalies using Z-score method
    std::vector<int> zScoreDetect(const json& column, double threshold = 3.0);
};

//
// --- GraphEngine ---
//
class GraphEngine {
public:
    // Add an edge between two nodes
    void addEdge(const std::string& from, const std::string& to);

    // Get neighbors of a node
    std::set<std::string> neighbors(const std::string& node) const;

    // Degree centrality (number of edges for a node)
    int degreeCentrality(const std::string& node) const;

    // Find connected components
    std::vector<std::set<std::string>> connectedComponents() const;

    // Shortest path between two nodes
    std::vector<std::string> shortestPath(const std::string& from, const std::string& to) const;

private:
    // Adjacency list: node → set of neighbors
    std::map<std::string, std::set<std::string>> m_adj;
};

//
// --- Core Facade ---
//
class Core {
public:
    Core();

    // Access to DataTable
    DataTable& data();

    // Access to Analyzer
    Analyzer& analyzer();

    // Access to GraphEngine
    GraphEngine& graph();

private:
    DataTable m_data;       ///< table data manager
    Analyzer m_analyzer;    ///< data analytics
    GraphEngine m_graph;    ///< graph algorithms
};
