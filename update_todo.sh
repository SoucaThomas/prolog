#!/bin/bash

# Script to automatically update todo.md based on [x] checkboxes
# Simply counts checked items in each phase

TODO_FILE="todo.md"
TEMP_FILE=$(mktemp)

# Count checkboxes for each phase using awk
phase1_done=$(awk '/^## Phase 1:/{flag=1} flag && /^## Phase [2-6]:/{flag=0} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase1_total=$(awk '/^## Phase 1:/{flag=1} flag && /^## Phase [2-6]:/{flag=0} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

phase2_done=$(awk '/^## Phase 2:/{flag=1} flag && /^## Phase [3-6]:/{flag=0} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase2_total=$(awk '/^## Phase 2:/{flag=1} flag && /^## Phase [3-6]:/{flag=0} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

phase3_done=$(awk '/^## Phase 3:/{flag=1} flag && /^## Phase [4-6]:/{flag=0} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase3_total=$(awk '/^## Phase 3:/{flag=1} flag && /^## Phase [4-6]:/{flag=0} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

phase4_done=$(awk '/^## Phase 4:/{flag=1} flag && /^## Phase [5-6]:/{flag=0} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase4_total=$(awk '/^## Phase 4:/{flag=1} flag && /^## Phase [5-6]:/{flag=0} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

phase5_done=$(awk '/^## Phase 5:/{flag=1} flag && /^## Phase 6:/{flag=0} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase5_total=$(awk '/^## Phase 5:/{flag=1} flag && /^## Phase 6:/{flag=0} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

phase6_done=$(awk '/^## Phase 6:/{flag=1} flag && /\[x\]/' "$TODO_FILE" | wc -l | tr -d ' ')
phase6_total=$(awk '/^## Phase 6:/{flag=1} flag && /\[[ x]\]/' "$TODO_FILE" | wc -l | tr -d ' ')

# Ensure all values are numbers (default to 0 if empty)
phase1_done=${phase1_done:-0}
phase1_total=${phase1_total:-0}
phase2_done=${phase2_done:-0}
phase2_total=${phase2_total:-0}
phase3_done=${phase3_done:-0}
phase3_total=${phase3_total:-0}
phase4_done=${phase4_done:-0}
phase4_total=${phase4_total:-0}
phase5_done=${phase5_done:-0}
phase5_total=${phase5_total:-0}
phase6_done=${phase6_done:-0}
phase6_total=${phase6_total:-0}

# Calculate totals
total_phases=6
completed_phases=0
[ "$phase1_done" -eq "$phase1_total" ] && [ "$phase1_total" -gt 0 ] && completed_phases=$((completed_phases + 1))
[ "$phase2_done" -eq "$phase2_total" ] && [ "$phase2_total" -gt 0 ] && completed_phases=$((completed_phases + 1))
[ "$phase3_done" -eq "$phase3_total" ] && [ "$phase3_total" -gt 0 ] && completed_phases=$((completed_phases + 1))
[ "$phase4_done" -eq "$phase4_total" ] && [ "$phase4_total" -gt 0 ] && completed_phases=$((completed_phases + 1))
[ "$phase5_done" -eq "$phase5_total" ] && [ "$phase5_total" -gt 0 ] && completed_phases=$((completed_phases + 1))
[ "$phase6_done" -eq "$phase6_total" ] && [ "$phase6_total" -gt 0 ] && completed_phases=$((completed_phases + 1))

total_tasks=$((phase1_total + phase2_total + phase3_total + phase4_total + phase5_total + phase6_total))
tasks_completed=$((phase1_done + phase2_done + phase3_done + phase4_done + phase5_done + phase6_done))

# Calculate percentages (handle division by zero)
p1_percent=$(awk -v done="$phase1_done" -v total="$phase1_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')
p2_percent=$(awk -v done="$phase2_done" -v total="$phase2_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')
p3_percent=$(awk -v done="$phase3_done" -v total="$phase3_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')
p4_percent=$(awk -v done="$phase4_done" -v total="$phase4_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')
p5_percent=$(awk -v done="$phase5_done" -v total="$phase5_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')
p6_percent=$(awk -v done="$phase6_done" -v total="$phase6_total" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')

overall_phase_percent=$(awk -v done="$completed_phases" -v total="$total_phases" 'BEGIN {printf "%.1f", (done / total) * 100}')
overall_task_percent=$(awk -v done="$tasks_completed" -v total="$total_tasks" 'BEGIN {if (total > 0) printf "%.1f", (done / total) * 100; else printf "0.0"}')

# Helper function to get status
get_status() {
    local done=$1
    local total=$2
    if [ "$done" -eq "$total" ] && [ "$total" -gt 0 ]; then
        echo "✅ Complete"
    elif [ "$done" -gt 0 ]; then
        echo "🟡 In Progress"
    else
        echo "⚪ Not Started"
    fi
}

p1_status=$(get_status "$phase1_done" "$phase1_total")
p2_status=$(get_status "$phase2_done" "$phase2_total")
p3_status=$(get_status "$phase3_done" "$phase3_total")
p4_status=$(get_status "$phase4_done" "$phase4_total")
p5_status=$(get_status "$phase5_done" "$phase5_total")
p6_status=$(get_status "$phase6_done" "$phase6_total")

# Update todo.md
awk -v p1_done="$phase1_done" -v p1_total="$phase1_total" -v p1_pct="$p1_percent" -v p1_stat="$p1_status" \
    -v p2_done="$phase2_done" -v p2_total="$phase2_total" -v p2_pct="$p2_percent" -v p2_stat="$p2_status" \
    -v p3_done="$phase3_done" -v p3_total="$phase3_total" -v p3_pct="$p3_percent" -v p3_stat="$p3_status" \
    -v p4_done="$phase4_done" -v p4_total="$phase4_total" -v p4_pct="$p4_percent" -v p4_stat="$p4_status" \
    -v p5_done="$phase5_done" -v p5_total="$phase5_total" -v p5_pct="$p5_percent" -v p5_stat="$p5_status" \
    -v p6_done="$phase6_done" -v p6_total="$phase6_total" -v p6_pct="$p6_percent" -v p6_stat="$p6_status" \
    -v phases_done="$completed_phases" -v total_phases="$total_phases" \
    -v tasks_done="$tasks_completed" -v total_tasks="$total_tasks" \
    -v overall_pct="$overall_phase_percent" -v task_pct="$overall_task_percent" '
BEGIN {
    in_phase1 = 0
    in_phase2 = 0
    in_phase3 = 0
    in_phase4 = 0
    in_phase5 = 0
    in_phase6 = 0
}
/^> \*\*Last Updated:\*\*/ {
    cmd = "date +\"%Y-%m-%d %H:%M:%S\""
    cmd | getline timestamp
    close(cmd)
    print "> **Last Updated:** " timestamp
    next
}
/^> \*\*Overall Progress:\*\*/ {
    print "> **Overall Progress:** " phases_done "/" total_phases " phases complete (" overall_pct "%) | " tasks_done "/" total_tasks " tasks complete (" task_pct "%)"
    next
}
/^\| Phase 1: Core Data Structures/ {
    print "| Phase 1: Core Data Structures    | " p1_stat " | " p1_done "/" p1_total " (" p1_pct "%) | " p1_done "/" p1_total " |"
    next
}
/^\| Phase 2: Unification Engine/ {
    print "| Phase 2: Unification Engine      | " p2_stat " | " p2_done "/" p2_total " (" p2_pct "%) | " p2_done "/" p2_total " |"
    next
}
/^\| Phase 3: Query Solver/ {
    print "| Phase 3: Query Solver            | " p3_stat " | " p3_done "/" p3_total " (" p3_pct "%) | " p3_done "/" p3_total " |"
    next
}
/^\| Phase 4: Simple REPL/ {
    print "| Phase 4: Simple REPL             | " p4_stat " | " p4_done "/" p4_total " (" p4_pct "%) | " p4_done "/" p4_total " |"
    next
}
/^\| Phase 5: Parser for Prolog Files/ {
    print "| Phase 5: Parser for Prolog Files | " p5_stat " | " p5_done "/" p5_total " (" p5_pct "%) | " p5_done "/" p5_total " |"
    next
}
/^\| Phase 6: Optional Enhancements/ {
    print "| Phase 6: Optional Enhancements   | " p6_stat " | " p6_done "/" p6_total " (" p6_pct "%) | " p6_done "/" p6_total " |"
    next
}
/^## Phase 1:/ { in_phase1 = 1; in_phase2 = 0; in_phase3 = 0; in_phase4 = 0; in_phase5 = 0; in_phase6 = 0; print; next }
/^## Phase 2:/ { in_phase2 = 1; in_phase1 = 0; in_phase3 = 0; in_phase4 = 0; in_phase5 = 0; in_phase6 = 0; print; next }
/^## Phase 3:/ { in_phase3 = 1; in_phase1 = 0; in_phase2 = 0; in_phase4 = 0; in_phase5 = 0; in_phase6 = 0; print; next }
/^## Phase 4:/ { in_phase4 = 1; in_phase1 = 0; in_phase2 = 0; in_phase3 = 0; in_phase5 = 0; in_phase6 = 0; print; next }
/^## Phase 5:/ { in_phase5 = 1; in_phase1 = 0; in_phase2 = 0; in_phase3 = 0; in_phase4 = 0; in_phase6 = 0; print; next }
/^## Phase 6:/ { in_phase6 = 1; in_phase1 = 0; in_phase2 = 0; in_phase3 = 0; in_phase4 = 0; in_phase5 = 0; print; next }
in_phase1 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p1_done "/" p1_total " tasks)")
    if (p1_done == p1_total && p1_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p1_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
in_phase2 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p2_done "/" p2_total " tasks)")
    if (p2_done == p2_total && p2_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p2_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
in_phase3 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p3_done "/" p3_total " tasks)")
    if (p3_done == p3_total && p3_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p3_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
in_phase4 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p4_done "/" p4_total " tasks)")
    if (p4_done == p4_total && p4_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p4_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
in_phase5 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p5_done "/" p5_total " tasks)")
    if (p5_done == p5_total && p5_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p5_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
in_phase6 && /^\*\*Status:\*\*/ {
    gsub(/\([0-9]+\/[0-9]+ tasks\)/, "(" p6_done "/" p6_total " tasks)")
    if (p6_done == p6_total && p6_total > 0) {
        gsub(/🟡 In Progress/, "✅ Complete")
        gsub(/⚪ Not Started/, "✅ Complete")
    } else if (p6_done == 0) {
        gsub(/🟡 In Progress/, "⚪ Not Started")
    }
    print; next
}
{ print }
' "$TODO_FILE" > "$TEMP_FILE"

mv "$TEMP_FILE" "$TODO_FILE"

echo "✅ Updated todo.md progress tracking"
echo "   Phase 1: $phase1_done/$phase1_total tasks ($p1_percent%)"
echo "   Phase 2: $phase2_done/$phase2_total tasks ($p2_percent%)"
echo "   Phase 3: $phase3_done/$phase3_total tasks ($p3_percent%)"
echo "   Phase 4: $phase4_done/$phase4_total tasks ($p4_percent%)"
echo "   Phase 5: $phase5_done/$phase5_total tasks ($p5_percent%)"
echo "   Phase 6: $phase6_done/$phase6_total tasks ($p6_percent%)"
echo "   Overall: $completed_phases/$total_phases phases complete | $tasks_completed/$total_tasks tasks complete"

# Format code files using clang-format
if command -v clang-format >/dev/null 2>&1; then
    echo ""
    echo "📝 Formatting code files..."
    find src include -name "*.cpp" -o -name "*.hpp" | while read -r file; do
        if [ -f "$file" ]; then
            clang-format -i "$file"
            echo "   Formatted: $file"
        fi
    done
    echo "✅ Code formatting complete"
else
    echo ""
    echo "⚠️  clang-format not found. Skipping code formatting."
fi
