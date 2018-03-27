/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

#ifndef	_UZFS_REBUILDING_H
#define	_UZFS_REBUILDING_H

#define	IO_DIFF_SNAPNAME	".io_snap"

/*
 * API to compare metadata
 * return :
 * 	-1 : if first < second
 *	 0 : if first == second
 *	 1 : if first > second
 */
int compare_blk_metadata(blk_metadata_t *first_md, blk_metadata_t *second_md);

/*
 * API to access data whose metadata is higer than base_metadata
 */
int uzfs_get_io_diff(zvol_state_t *zv, blk_metadata_t *base_metadata,
    uzfs_get_io_diff_cb_t *cb_func, off_t offset, size_t len, void *arg);

/*
 * uzfs_search_nonoverlapping_io will check on_disk metadata with w_metadata and
 * will populate list with non-overlapping segment(offset,len).
 * IO's will be compared by meta_vol_block_size. If on_disk metadata is greater
 * than w_metadata then that part of IO's will be discarded else it will be
 * added to list.
 */
int uzfs_search_nonoverlapping_io(zvol_state_t *zv, uint64_t offset,
    uint64_t len, blk_metadata_t *w_metadata, void **list);
#endif
