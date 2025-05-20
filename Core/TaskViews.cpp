#include "TaskViews.h"
#include "Tools/format_time.h"
#include <algorithm>
#include <iomanip>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
/* Local Tools */
namespace {

void inline __filled_col_widths(
    std::vector<size_t>& col_widths,
    const std::string& what, ssize_t which) {
	col_widths[which] = std::max(col_widths[which], what.size());
}

void inline filled_col_width(
    std::vector<size_t>& col_widths, const Task* which) {
	__filled_col_widths(col_widths, which->get_task_name(), TasksListView::COL_INDEX::NAME);
	__filled_col_widths(col_widths, which->get_discriptions(), TasksListView::COL_INDEX::DESP);
	__filled_col_widths(
	    col_widths,
	    ChronoTools::fromDdlTimeToReadableString(which->get_deadline()),
	    TasksListView::COL_INDEX::DDL);
	__filled_col_widths(
	    col_widths,
	    taskPrioirtyString(which->get_priority()),
	    TasksListView::COL_INDEX::PRIORITY);
}

}

std::string TasksListView::format_tasklists_view(const std::vector<std::shared_ptr<Task>>& tasks) {
	std::ostringstream oss;
	auto col_widths = headers
	    | std::views::transform([](auto& h) { return h.size(); })
	    | std::ranges::to<std::vector>(); 

	auto append_sep = [&]() {
		oss << '+';
		for (size_t w : col_widths) {
			oss << std::string(w + 2, '-') << '+';
		}
		oss << "\n";
	};

	auto append_row = [&](const std::vector<std::string>& cols) {
		oss << '|';
		for (size_t i = 0; i < cols.size(); ++i) {
			oss << ' ' << std::left << std::setw(col_widths[i]) << cols[i] << ' ' << '|';
		}
		oss << "\n";
	};

	auto append_headers = [&]() {
		oss << '|';
		for (size_t i = 0; i < headers.size(); ++i) {
			oss << ' ' << std::left << std::setw(col_widths[i]) << headers[i] << ' ' << '|';
		}
		oss << "\n";
	};

	std::ranges::for_each(
	    tasks,
	    [&](const auto& tp) {
		    filled_col_width(col_widths, tp.get());
	    });

	// Header
	append_sep();
	append_headers();
	append_sep();
	// Data rows
	for (auto& tp : tasks) {
		auto packages = {
			tp->get_task_name(),
			tp->get_discriptions(),
			ChronoTools::fromDdlTimeToReadableString(tp->get_deadline()),
			taskPrioirtyString(tp->get_priority()),
		};
		append_row(packages);
	}
	append_sep();
	return oss.str();
}

std::string TasksListView::format_tasklists_view(
    const std::vector<std::shared_ptr<Task>>& l,
    std::function<std::string(const std::vector<std::shared_ptr<Task>>& l)> f) {
	return f(l);
}