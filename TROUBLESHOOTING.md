# Troubleshooting

## Logs

AI File Sorter writes three rotating log files:

- `core.log`
- `db.log`
- `ui.log`

### Log locations

- Windows: `%APPDATA%\AIFileSorter\logs`
- Linux: `$XDG_CACHE_HOME/AIFileSorter/logs`
- Linux fallback: `~/.cache/AIFileSorter/logs`

### Log rotation

Each log file rotates at `5 MiB` and keeps `3` rolled files.

That means each log stream keeps:

- the active file
- up to `3` older rotated files
- about `20 MiB` total per stream including the active file

If you are troubleshooting backend selection, model loading, or packaging issues, start with `core.log`.
